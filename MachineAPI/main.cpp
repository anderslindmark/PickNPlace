#include <iostream>
//#include "MachineController.h"
//#include "TestCommand.h"
#include "SerialPort.h"
using namespace std;

void main() {
	BYTE b;
	SerialPort sp("com1");
	sp.initialize();
	sp.configurePort(9600,8,TRUE, EVENPARITY,ONESTOPBIT);
	sp.setCommunicationTimeouts(0,1,500,0,0);
	sp.writeString("RD 1915\n");

	sp.readByte(b);
	cout << (int) b << endl;
	sp.readByte(b);
	cout << (int) b << endl;
	sp.readByte(b);
	cout << (int) b << endl;
}