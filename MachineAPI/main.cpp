#include <iostream>
#include "MachineController.h"
//#include "TestCommand.h"
#include "SerialPort.h"

using namespace std;

void readReg(string reg);
void storeReg(string reg);
void writeReg(string reg, string val);
void writeCmd(string cmd, string ret);

void own(MachineEvent *e);

SerialPort sp("com1");
BYTE b;

#define XAXIS 1
#define HEJX(a)	"WR ASD"#a"HH"

int main(void) 
{
	int a = 3;
	cout << HEJX(1) << endl;
}

/*
int main(void)
{
	string tmp;
	MachineController mc("com1");
	if (!mc.initialize())
	{
		cout << "Error initializing MachineController\n";
		return FALSE;
	}
	mc.addEventHandler(&own);
	mc.runCommand(*(new MachineMoveAbsoluteCommand(AXIS_X, 10000)));
	cout << "Waiting\n";
	mc.wait();
	cout << "Done\n";
	cin >> tmp;

}

void own(MachineEvent *e)
{
	cout << "EVENT MSG: " << e->getEventMsg() << endl;
	delete e;
}
*/