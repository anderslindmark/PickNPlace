#include "DiagonalTest.h"
#include <sstream>
DiagonalTest::DiagonalTest(void)
{
}

DiagonalTest::~DiagonalTest(void)
{
}

string DiagonalTest::ToString()
{
	return string("Test Diagonal");
}

MachineState DiagonalTest::GetAfterState(MachineState &oldms)
{
	MachineStateStruct mss = oldms.GetState();
	mss.x = 470000;
	mss.y = 193000;

	return MachineState(mss);
}

bool DiagonalTest::DoCommand(SerialPort &sp)
{
	int xpos = 470000/10;
	int ypos = 193000/5;
	
	int pos;
	stringstream c1, c2;
	char ycmd[20];
	char xcmd[20];
	
	pos = xpos;
	c1 << M_POS_ABS_MOVE_X;
	strcpy_s(xcmd, c1.str().c_str());
	
	pos = ypos;
	c2 << M_POS_ABS_MOVE_Y;
	strcpy_s(ycmd, c2.str().c_str());

	
	ExecCommand(sp, M_READY_1515,		M_ANS_1);
	
	ExecCommand(sp, M_DO_ABS_MOVE_X,	M_ANS_OK);
	ExecCommand(sp, M_DO_ABS_MOVE_Y,	M_ANS_OK);

	ExecCommand(sp, xcmd,			M_ANS_OK);
	ExecCommand(sp, ycmd,			M_ANS_OK);

	ExecCommand(sp, M_STORE_ABS_MOVE_X,	M_ANS_OK);
	ExecCommand(sp, M_STORE_ABS_MOVE_Y,	M_ANS_OK);

	ExecCommand(sp, M_EXEC_MOVE_X,		M_ANS_OK);
	ExecCommand(sp, M_EXEC_MOVE_Y,		M_ANS_OK);

	ExecCommand(sp, M_READY_1515,		M_ANS_1);

	return true;
}

DiagonalTest* DiagonalTest::Copy()
{
	return new DiagonalTest();
}