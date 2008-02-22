#include "MachineCommand.h"
#include <iostream>

//
//
using namespace std;
//MachineCommand::MachineCommand() {}
//MachineCommand::~MachineCommand() {}
//int MachineCommand::getCommand() {
//	return 4564;
//}

bool MachineCommand::execCommand(SerialPort &sp, const char *cmd, const char *ret)
{
	char ans[5];
	do
	{
		// TODO: Check for errors in write/readLine in sp.
		sp.writeLine(cmd);
		sp.readLine(ans);

		if (strcmp(ans, M_ANS_ERROR) == 0)
		{
			sp.writeLine(M_DO_CR);
			sp.readLine(ans);
			if (strcmp(ans, M_ANS_CC) != 0)
			{
				// TODO: Set errormsg somewhere
				cout << "MachineCommand::execCommand: Expected 'CC', recieved " << ans << endl;
				return false;
			}
			else
			{
				continue;
			}
		}
	} while (strcmp(ans, ret) != 0);
	return true;
}
