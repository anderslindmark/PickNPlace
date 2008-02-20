#include "SerialPort.h"

SerialPort::SerialPort(string portName)
{
	_portName = portName;
}

SerialPort::~SerialPort(void)
{
}

bool SerialPort::initialize() {
	string portName = "//./" + _portName;

	port = CreateFile(portName.c_str(),
						  GENERIC_READ | GENERIC_WRITE,
						  0,
						  0,
						  OPEN_EXISTING,
						  0,
						  0);
	if(port==INVALID_HANDLE_VALUE)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool SerialPort::configurePort(DWORD BaudRate, BYTE ByteSize,
							   DWORD fParity, BYTE Parity,
							   BYTE StopBits)
{
	if((m_bPortReady = GetCommState(port, &m_dcb))==0)
	{
		CloseHandle(port);
		return false;
	}
	m_dcb.BaudRate =BaudRate;
	m_dcb.ByteSize = ByteSize;
	m_dcb.Parity =Parity ;
	m_dcb.StopBits =StopBits;
	m_dcb.fBinary=TRUE;
	m_dcb.fDsrSensitivity=false;
	m_dcb.fParity=fParity;
	m_dcb.fOutX=false;
	m_dcb.fInX=false;
	m_dcb.fNull=false;
	m_dcb.fAbortOnError=TRUE;
	m_dcb.fOutxCtsFlow=FALSE;
	m_dcb.fOutxDsrFlow=false;
	m_dcb.fDtrControl=DTR_CONTROL_DISABLE;
	m_dcb.fDsrSensitivity=false;
	m_dcb.fRtsControl=RTS_CONTROL_DISABLE;
	m_dcb.fOutxCtsFlow=false;
	m_dcb.fOutxCtsFlow=false;

	m_bPortReady = SetCommState(port, &m_dcb);
	if(m_bPortReady ==0)
	{
		CloseHandle(port);
		return false;
	}
	return true;
}

bool SerialPort::setCommunicationTimeouts(DWORD ReadIntervalTimeout,
										  DWORD ReadTotalTimeoutMultiplier,
										  DWORD ReadTotalTimeoutConstant,
										  DWORD WriteTotalTimeoutMultiplier,
										  DWORD WriteTotalTimeoutConstant)
{
	if((m_bPortReady = GetCommTimeouts (port, &m_CommTimeouts))==0)
	{
		return false;
	}
	m_CommTimeouts.ReadIntervalTimeout =ReadIntervalTimeout;
	m_CommTimeouts.ReadTotalTimeoutConstant =ReadTotalTimeoutConstant;
	m_CommTimeouts.ReadTotalTimeoutMultiplier
		=ReadTotalTimeoutMultiplier;
	m_CommTimeouts.WriteTotalTimeoutConstant
		= WriteTotalTimeoutConstant;
	m_CommTimeouts.WriteTotalTimeoutMultiplier
		=WriteTotalTimeoutMultiplier;
	m_bPortReady = SetCommTimeouts (port, &m_CommTimeouts);
	if(m_bPortReady ==0)
	{
		CloseHandle(port);
		return false;
	}
	return true;
}

bool SerialPort::writeByte(BYTE bybyte)
{
	iBytesWritten=0;
	if(WriteFile(port,&bybyte,1,&iBytesWritten,NULL)==0)
	{
		return false;
	}
	else 
	{
		return true;
	}
}

bool SerialPort::writeString(string s)
{
	const char *ch = s.c_str();
	int i = 0;
	while (ch[i] != '\0')
	{
		if (!writeByte(ch[i]))
		{
			return false;
		}
	}
	return true;
}

bool SerialPort::readByte(BYTE &resp)
{
	BYTE rx;
	resp=0;

	DWORD dwBytesTransferred=0;

	if (ReadFile (port, &rx, 1, &dwBytesTransferred, 0))
	{
		if (dwBytesTransferred == 1)
		{
			resp=rx;
			return true;
		}
	}
	return false;
}

void SerialPort::closePort()
{
	CloseHandle(port);
	return;
}