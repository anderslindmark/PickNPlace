/**
 	\file SerialPort.h
 
 	\brief
 	Header file for the SerialPort class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__

#include "windows.h"
#include <string>
using namespace std;

/// \class SerialPort
/// \brief Used for communication over a serial port
///
/// The communication must first be opened, this is done through the
/// public member function Initialize. The communication can then 
/// be configured through member functions ConfigurePort and SetCommunicationTimeouts.
/// The port should be closed when finnished using it.
class SerialPort
{
public:
	/// \brief Constructor
	///
	/// \param portName name of the serial port
	SerialPort(string portName);

	/// \brief Destructor
	~SerialPort(void);

	/// \brief Initialize the serial port, must be runned first
	bool initialize();

	/// \brief Configure the port
	///
	/// \return true if configureation succeesed else false
	bool configurePort(); /*DWORD BaudRate, BYTE ByteSize,
							   DWORD fParity, BYTE Parity,
							   BYTE StopBits); */

	/// \brief Set communication timeout times
	///
	/// \param ReadIntervalTimeout
	/// \param ReadTotalTimeoutMultiplier
	/// \param ReadTotalTimeoutConstant
	/// \param WriteTotalTimeoutMultiplier
	/// \param WriteTotalTimeoutConstant
	/// \return true if configureation succeesed else false
	bool setCommunicationTimeouts(DWORD ReadIntervalTimeout,
										  DWORD ReadTotalTimeoutMultiplier,
										  DWORD ReadTotalTimeoutConstant,
										  DWORD WriteTotalTimeoutMultiplier,
										  DWORD WriteTotalTimeoutConstant);

	/// \brief Write a byte to the serial port
	///
	/// \param bybyte byte to be written
	/// \return true if succeeded else false
	bool writeByte(BYTE bybyte);

	/// \brief Write a line to the serial port, will be terminated with a CR
	///
	/// \param s line to be written
	/// \return true if succeeded else false
	bool writeLine(const char *s);

	/// \brief Read a byte from the serial port
	///
	/// \param resp where the byte should be read
	/// \return true if succeeded else false
	bool readByte(BYTE &resp);

	/// \brief Read a line from the serial port, lines will be divided with a CR NL
	///
	/// \param sin where the line should be read
	/// \return true if succeeded else false
	bool readLine(char *sin);

	/// \brief Close the serial port
	void closePort();

private:
	string _portName; ///<The name of the serial port
	HANDLE port; ///<Handler for the serial port
	DCB      m_dcb;
	COMMTIMEOUTS m_CommTimeouts;
	BOOL     m_bPortReady;
	BOOL     bWriteRC;
	BOOL     bReadRC;
	DWORD iBytesWritten;
	DWORD iBytesRead;
	DWORD dwBytesRead;
};

#endif //__SERIALPORT_H__