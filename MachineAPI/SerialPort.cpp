/**
 	\file SerialPort.cpp
 
 	\brief
 	Source file for the SerialPort class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#include "SerialPort.h"
#include "MachineEvent.h"
#include <string>
#include <iostream>


using namespace std;

SerialPort::SerialPort(string portName)
{
	_portName = portName;
}

SerialPort::~SerialPort(void)
{
}

bool SerialPort::Initialize() {
	string portName = "//./" + _portName;

	port = CreateFile(portName.c_str(),
						  GENERIC_READ | GENERIC_WRITE,
						  0,
						  NULL,
						  OPEN_EXISTING,
						  0,
						  NULL);
	if(port==INVALID_HANDLE_VALUE)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool SerialPort::ConfigurePort() //DWORD BaudRate, BYTE ByteSize,
							   //BYTE Parity, BYTE StopBits) //DWORD fParity,
{
	SecureZeroMemory(&m_dcb, sizeof(DCB));
    m_dcb.DCBlength = sizeof(DCB);
	if((m_bPortReady = GetCommState(port, &m_dcb))==0)
	{
		CloseHandle(port);
		return false;
	}

	m_dcb.BaudRate = 9600;
	m_dcb.ByteSize = 8;
	m_dcb.StopBits = ONESTOPBIT;
	m_dcb.ErrorChar = 63;
	m_dcb.Parity = EVENPARITY;

	m_dcb.fRtsControl = RTS_CONTROL_DISABLE;
	m_dcb.fInX = false;
	m_dcb.fOutX = false;

	m_dcb.fDtrControl=DTR_CONTROL_ENABLE;
	m_dcb.fRtsControl=RTS_CONTROL_ENABLE;
	m_dcb.fDsrSensitivity=false;

	m_dcb.fBinary=true;
	m_dcb.fDsrSensitivity=false;
	m_dcb.fParity=true;

	m_dcb.fNull=false;
	m_dcb.fAbortOnError=TRUE;
	m_dcb.fOutxCtsFlow=FALSE;
	m_dcb.fOutxDsrFlow=false;
	m_dcb.fOutxCtsFlow=false;
	m_dcb.fOutxCtsFlow=false;
	m_dcb.XonLim = 80;
	m_dcb.XoffLim = 80;

	m_bPortReady = SetCommState(port, &m_dcb);
	if(m_bPortReady ==0)
	{
		CloseHandle(port);
		return false;
	}
	return true;
}
// SetCommunicationTimeouts(0, 2, 5000, 2, 5000);
bool SerialPort::SetCommunicationTimeouts(DWORD ReadIntervalTimeout,
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

bool SerialPort::WriteByte(BYTE bybyte)
{
	iBytesWritten=0;
	if(WriteFile(port,&bybyte,1,&iBytesWritten,NULL)==0)
	{
		throw MachineEvent(EVENT_SERIAL_WRITEERROR, "Serial port write error!");
		//return false;
	}
	else 
	{
		return true;
	}
}

bool SerialPort::WriteLine(const char *ch)
{
	//cout << "\nDEBUG: SerialPort::WriteLine\t" << ch << endl;
	//const char *ch = s.c_str();
	//for (i = 0; i < c.length(); i++)
	for (unsigned int i = 0; i < strlen(ch); i++)
	{
		if (!WriteByte(ch[i]))
		{
			return false;
		}
		//cout << "Sent byte " << ch[i] << "\n";
	}
	WriteByte('\r');
	//cout << "Sent byte \\r\n";
	return true;
}

bool SerialPort::ReadByte(BYTE &resp)
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
	throw MachineEvent(EVENT_SERIAL_READERROR, "Serial port read error!");
	//return false;
}

bool SerialPort::ReadLine(char *sin, int bufsize)
{
	BYTE prev = 0;
	BYTE cur = 0;
	string s;
	string read = "";

	if (!sin)
		return false;

	while (prev != 13 && cur != 10) 
	{
		prev = cur;
		if (!ReadByte(cur)) 
		{
			return false;
		}
		read.append(1, (char)cur);
	}
	s = read.substr(0, read.length()-2);
	strcpy_s(sin, bufsize, s.c_str());

	// cout << "\nDEBUG: SerialPort::ReadLine\t" << sin << endl;
	return true;
}

void SerialPort::ClosePort()
{
	CloseHandle(port);
	return;
}