#include <iostream>
#include "MachineController.h"
//#include "TestCommand.h"
//#include "SerialPort.h"

using namespace std;

void readReg(string reg);
void storeReg(string reg);
void writeReg(string reg, string val);
void writeCmd(string cmd, string ret);

void own(MachineEvent *e);

SerialPort sp("com1");
BYTE b;

int main(void)
{
	int xp, yp, zp;
	float rp;
	string tmp;
	MachineController mc("com1");
	mc.addEventHandler(&own);
	if (!mc.initializeMachine())
	{
		cout << "Error initializing MachineController\n";
		return FALSE;
	}
	mc.wait();
	
	//mc.runCommand(*(new MachineInitCommand())); mc.wait();

	for (;;)
	{
		printf("x y z r: ");
		scanf_s("%d %d %d %f", &xp, &yp, &zp, &rp);
		mc.runCommand(*(new MachineMoveAbsoluteCommand(AXIS_X, xp))); mc.wait();
		mc.runCommand(*(new MachineMoveAbsoluteCommand(AXIS_Y, yp))); mc.wait();
		mc.runCommand(*(new MachineMoveAbsoluteCommand(AXIS_Z, zp))); mc.wait();
		mc.runCommand(*(new MachineRotateAbsoluteCommand(rp))); mc.wait();
	}

	/*
	mc.runCommand(*(new MachineMoveAbsoluteCommand(AXIS_X, 0))); mc.wait();
	mc.runCommand(*(new MachineMoveAbsoluteCommand(AXIS_Y, 0))); mc.wait();
	mc.runCommand(*(new MachineMoveAbsoluteCommand(AXIS_Z, 0))); mc.wait();

	mc.runCommand(*(new MachineMoveAbsoluteCommand(AXIS_X, 20000))); mc.wait();
	mc.runCommand(*(new MachineMoveAbsoluteCommand(AXIS_Y, 30000))); mc.wait();
	mc.runCommand(*(new MachineMoveAbsoluteCommand(AXIS_Z, 8000))); mc.wait();
	*/
	cout << "Done\n";
	cin >> tmp;

}

void own(MachineEvent *e)
{
	cout << "EVENT MSG: " << e->getEventMsg() << endl;
	delete e;
}
