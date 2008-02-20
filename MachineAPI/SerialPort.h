#pragma once
#include "windows.h"
#include <string>
using namespace std;

class SerialPort
{
public:
	SerialPort(string portName);
	~SerialPort(void);
	bool initialize();
	bool configurePort(DWORD BaudRate, BYTE ByteSize,
							   DWORD fParity, BYTE Parity,
							   BYTE StopBits);
	bool setCommunicationTimeouts(DWORD ReadIntervalTimeout,
										  DWORD ReadTotalTimeoutMultiplier,
										  DWORD ReadTotalTimeoutConstant,
										  DWORD WriteTotalTimeoutMultiplier,
										  DWORD WriteTotalTimeoutConstant);
	bool writeByte(BYTE bybyte);
	bool writeString(string s);
	bool readByte(BYTE &resp);
	void closePort();

private:
	string _portName;
	HANDLE port;
	DCB      m_dcb;
	COMMTIMEOUTS m_CommTimeouts;
	BOOL     m_bPortReady;
	BOOL     bWriteRC;
	BOOL     bReadRC;
	DWORD iBytesWritten;
	DWORD iBytesRead;
	DWORD dwBytesRead;
};
