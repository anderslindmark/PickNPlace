#include <iostream>
//#include "MachineController.h"
//#include "TestCommand.h"
#include "SerialPort.h"
using namespace std;

void readReg(string reg);
void storeReg(string reg);
void writeReg(string reg, string val);
void writeCmd(string cmd, string ret);

SerialPort sp("com1");
BYTE b;

int main() 
{
	cout << "Start" << endl;
	cout << "Initializing serial port\n";
	if (!sp.initialize()) {
		cout<< "COULDNT OPEN PORT!" << endl;
		return 0;
	}
	cout << "Configuring serial port\n";
	sp.configurePort();//9600, 8, TRUE, EVENPARITY, ONESTOPBIT);
	cout << "Setting timeouts\n";
	sp.setCommunicationTimeouts(0,0,0,0,0);
	
	writeCmd("RD 1915", "1");
	writeCmd("ST 1900", "OK");

	writeCmd("RD 1915", "1");
	writeCmd("RD 1515", "1");
	writeCmd("CR", "CC");
	writeCmd("RD 1915", "1");
	writeCmd("RD 1915", "1");
	writeCmd("ST 1800", "OK");
	writeCmd("RD 1915", "1");
	writeCmd("WR DM215 400", "OK");
	writeCmd("RD 1915", "1");
	writeCmd("WR DM213 0", "OK");
	writeCmd("RD 1915", "1");
	writeCmd("WS T35 0", "OK");
	writeCmd("RD 1915", "1");
	writeCmd("WS T36 0", "OK");
	writeCmd("RD 1915", "1");
	writeCmd("WS T37 0", "OK");
	writeCmd("RD 1915", "1");
	writeCmd("WR DM210 57346", "OK");
	writeCmd("RD 1915", "1");
	writeCmd("WR DM211 257", "OK");
	writeCmd("RD 1915", "1");
	writeCmd("RD 1915", "1");
	writeCmd("WR DM300 35328", "OK");
	writeCmd("WR DM301 2500", "OK");
	writeCmd("WR DM51 2", "OK");
	writeCmd("WR DM50 300", "OK");
	writeCmd("RD 1915", "1");
	writeCmd("RD 1915", "1");


	cout << "Done..\n";
}

void writeCmd(string cmd, string ret)
{
	cout << "Sending command " << cmd << endl;
	string get;
	do {
		
		sp.writeLine(cmd);

		cout << "Waiting...\n";
		cout << "READING LINE" << endl;
		if (!sp.readLine(get)) {
			cout << "ERROR"<< endl;
		}
		cout << "GOT :" << get << endl;
//		cout << "RET :" << ret.length() << endl;
	} while (ret != get); 
}
