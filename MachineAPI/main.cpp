#include <iostream>
//#include "MachineController.h"
//#include "TestCommand.h"
#include "SerialPort.h"
using namespace std;

void readReg(string reg);
void storeReg(string reg);
void writeReg(string reg, string val);
void writeCmd(string cmd);

SerialPort sp("com1");
BYTE b;

void main() 
{
	cout << "Start" << endl;
	cout << "Initializing serial port\n";
	sp.initialize();
	cout << "Configuring serial port\n";
	sp.configurePort(9600, 8, TRUE, EVENPARITY, ONESTOPBIT);
	cout << "Setting timeouts\n";
	sp.setCommunicationTimeouts(0,1,500,0,0);
	
	writeCmd("RD 1915");
	//writeCmd("ST 1900");
	/*
	writeCmd("RD 1915");
	writeCmd("RD 1515");
	writeCmd("ST 1800");
	writeCmd("RD 1915");
	writeCmd("WR DM215 400");
	writeCmd("RD 1915");
	writeCmd("WR DM213 0");
	writeCmd("RD 1915");
	writeCmd("WS T35 0");
	writeCmd("RD 1915");
	writeCmd("WS T36 0");
	writeCmd("RD 1915");
	writeCmd("WS T37 0");
	writeCmd("RD 1915");
	writeCmd("WR DM210 57346");
	writeCmd("RD 1915");
	writeCmd("WR DM211 257");
	writeCmd("RD 1915");
	*/

	cout << "Done..\n";
}

void writeCmd(string cmd)
{
	cout << "Sending command\n";
	sp.writeString(cmd);

	cout << "Waiting...\n";
	bool done = FALSE;
	/*
	while(!done)
	{
	*/
	for (int i = 0; i < 20; i++)
	{
		sp.readByte(b);
		if (b == '1') done = TRUE;
		cout << (int) b << " - \"" << (char) b << "\"" << endl;
	}
}
