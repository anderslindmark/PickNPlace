#include <iostream>
#include "MachinePolygon.h"

#include "MachineController.h"
#include "MachineCommands.h"
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
	string tmp;
	MachineController mc("com1");
	mc.AddEventHandler(&own);
	if (!mc.InitializeMachine())
	{
		cout << "Error initializing MachineController\n";
		return FALSE;
	}
	mc.Wait();
/*
	mc.RunCommand(*(new MachineLightBrightnessCommand(LAMP_CAMERA, 3))); mc.Wait();

	for (;;)
	{
		mc.RunCommand(*(new MachineMoveRelativeCommand(AXIS_Z, 1000))); mc.Wait();
		cin >> tmp;
	}
*/

	/*
	int i = 0;
	for(;;)
	{
		mc.RunCommand(*(new MachineLightBrightnessCommand(LAMP_CAMERA, i))); mc.Wait();
		mc.RunCommand(*(new MachineLightBrightnessCommand(LAMP_LOOKUP, 15-i))); mc.Wait();
		i++;
		if (i == 16) i = 0;
	}
*/


	/*
	//mc.RunCommand(DiagonalTest()); mc.Wait();
	//mc.RunCommand(*(new MachineInitCommand())); mc.Wait();
	for (;;)
	{
		printf("x y z ");
		scanf_s("%d %d %d", &xp, &yp, &zp);
		mc.RunCommand(*(new MachineMoveAbsoluteCommand(AXIS_X, xp))); mc.Wait();
		mc.RunCommand(*(new MachineMoveAbsoluteCommand(AXIS_Y, yp))); mc.Wait();
		mc.RunCommand(*(new MachineMoveAbsoluteCommand(AXIS_Z, zp))); mc.Wait();

	}
	*/
	//mc.RunCommand(*(new MachineMoveAllCommand(200000, 90000, 0))); mc.Wait();
	//mc.RunCommand(*(new MachineMoveNeedleCommand(NEEDLEMOVEMENT_DOWN))); mc.Wait();


	

	mc.RunCommand(*(new MachineSetDispenceTimeCommand(DISPENCETIME_AFTER, 1))); mc.Wait();
	mc.RunCommand(*(new MachineSetDispenceTimeCommand(DISPENCETIME_BEFORE, 1))); mc.Wait();
	mc.RunCommand(*(new MachineSetDispenceTimeCommand(DISPENCETIME_SUCKBACK, 1))); mc.Wait();

	mc.RunCommand(*(new MachineSetDispenceOffsetCommand(OFFSET_Z, 8000))); mc.Wait();
	mc.RunCommand(*(new MachineSetDispenceOffsetCommand(OFFSET_ZS, 200))); mc.Wait();
	mc.RunCommand(*(new MachineSetDispenceOffsetCommand(OFFSET_TURN, 2000))); mc.Wait();

	
	/*
	MachinePolygon mp;
	mp.AddPoint(MachinePolygonPoint(10000, 10000));
	mp.AddPoint(MachinePolygonPoint(10000, 50000));
	
	mp.AddPoint(MachinePolygonPoint(20000, 50000));
	mp.AddPoint(MachinePolygonPoint(20000, 10000));
	
	mp.AddPoint(MachinePolygonPoint(30000, 10000));
	mp.AddPoint(MachinePolygonPoint(30000, 50000));

	mp.AddPoint(MachinePolygonPoint(40000, 50000));
	mp.AddPoint(MachinePolygonPoint(40000, 10000));
	
	mc.RunCommand(*(new MachinePolygonDispenceCommand(mp))); mc.Wait();
*/

	//mc.RunCommand(*(new MachineMoveAllCommand(1000, 1000, 0))); mc.Wait();

//	mc.RunCommand(*(new MachineSetDispenceSpeedCommand(5))); mc.Wait();
	
	MachinePolygon mp;
	mp.AddPoint(MachinePolygonPoint(1000, 1000));
	mp.AddPoint(MachinePolygonPoint(1000, 50000));
	mp.AddPoint(MachinePolygonPoint(50000,50000));
	mp.AddPoint(MachinePolygonPoint(50000,1000));
/*
	mc.RunCommand(*(new MachineSetDispenceSpeedCommand(2))); mc.Wait();
	mc.RunCommand(*(new MachinePolygonDispenceCommand(mp))); mc.Wait();

	mc.RunCommand(*(new MachinePolygonDispenceCommand(mp))); mc.Wait();
*/
	mc.RunCommand(MachineMoveAllCommand(300000, 190000, 5000)); mc.Wait();
	MachineWrapperCommand wrapper;
	wrapper.Add(*(new MachineSetDispenceSpeedCommand(2)));
	wrapper.Add(*(new MachinePolygonDispenceCommand(mp)));
	wrapper.Add(*(new MachineSetDispenceSpeedCommand(6)));
	wrapper.Add(*(new MachineSetDispenceOffsetCommand(OFFSET_X, 10000)));
	wrapper.Add(*(new MachinePolygonDispenceCommand(mp)));
	mc.RunCommand(wrapper); mc.Wait();

	//mc.RunCommand(*(new MachineParkCommand())); mc.Wait();

/*	mc.RunCommand(*(new MachineMoveNeedleCommand(NEEDLEMOVEMENT_DOWN))); mc.Wait();
	mc.RunCommand(*(new MachineMoveAllCommand(1000, 1000, 8000))); mc.Wait();
	cin >> tmp;
	mc.RunCommand(*(new MachineMoveAllCommand(100000, 100000, 8000))); mc.Wait();
*/
	/*
	mc.RunCommand(*(new MachineMoveAllCommand(350000, 190000, 5000))); mc.Wait();
	mc.RunCommand(*(new MachineMoveAllCommand(-1, 0, 0))); mc.Wait();
	*/

	/*
	mc.RunCommand(*(new MachineMoveAbsoluteCommand(AXIS_X, 0))); mc.Wait();
	mc.RunCommand(*(new MachineMoveAbsoluteCommand(AXIS_Y, 0))); mc.Wait();
	mc.RunCommand(*(new MachineMoveAbsoluteCommand(AXIS_Z, 0))); mc.Wait();

	mc.RunCommand(*(new MachineMoveAbsoluteCommand(AXIS_X, 20000))); mc.Wait();
	mc.RunCommand(*(new MachineMoveAbsoluteCommand(AXIS_Y, 30000))); mc.Wait();
	mc.RunCommand(*(new MachineMoveAbsoluteCommand(AXIS_Z, 8000))); mc.Wait();
	*/
	//cout << "Done\n";
	//cin >> tmp;

}


void own(MachineEvent *e)
{
	cout << "\nEVENT MSG: " << e->GetEventMsg() << endl << endl;
	delete e;
}

