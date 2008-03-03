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
	mc.AddEventHandler(&own);
	if (!mc.InitializeMachine())
	{
		cout << "Error initializing MachineController\n";
		return FALSE;
	}
	mc.Wait();
	
	//mc.RunCommand(DiagonalTest()); mc.Wait();
	//mc.RunCommand(*(new MachineInitCommand())); mc.Wait();
	for (;;)
	{
		printf("x y z r: ");
		scanf_s("%d %d %d %f", &xp, &yp, &zp, &rp);
		if (xp == -1)
		{
			mc.RunCommand(*(new MachineMoveRelativeCommand(AXIS_X, -2000))); mc.Wait();
		}
		else if (xp == -2)
		{
			break;
		}
		else
		{
			mc.RunCommand(*(new MachineMoveAbsoluteCommand(AXIS_X, xp))); mc.Wait();
			mc.RunCommand(*(new MachineMoveAbsoluteCommand(AXIS_Y, yp))); mc.Wait();
			mc.RunCommand(*(new MachineMoveAbsoluteCommand(AXIS_Z, zp))); mc.Wait();
			mc.RunCommand(*(new MachineRotateAbsoluteCommand(rp))); mc.Wait();
		}
		
	}

	mc.RunCommand(*(new MachineParkCommand())); mc.Wait();


	/*
	mc.RunCommand(*(new MachineMoveAbsoluteCommand(AXIS_X, 0))); mc.Wait();
	mc.RunCommand(*(new MachineMoveAbsoluteCommand(AXIS_Y, 0))); mc.Wait();
	mc.RunCommand(*(new MachineMoveAbsoluteCommand(AXIS_Z, 0))); mc.Wait();

	mc.RunCommand(*(new MachineMoveAbsoluteCommand(AXIS_X, 20000))); mc.Wait();
	mc.RunCommand(*(new MachineMoveAbsoluteCommand(AXIS_Y, 30000))); mc.Wait();
	mc.RunCommand(*(new MachineMoveAbsoluteCommand(AXIS_Z, 8000))); mc.Wait();
	*/
	cout << "Done\n";
	cin >> tmp;

}

void own(MachineEvent *e)
{
	cout << "EVENT MSG: " << e->GetEventMsg() << endl;
	delete e;
}
