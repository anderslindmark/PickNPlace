/**
 	\file MachineCommand.cpp
 
 	\brief
 	Source file for the MachineCommand
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#include "MachineCommand.h"
#include "MachineEvent.h"
#include <iostream>

using namespace std;

bool MachineCommand::ExecCommand(SerialPort &sp, const char *cmd, const char *ret)
{
	char ans[5];

	do
	{
		// TODO: Check for errors in write/ReadLine in sp.
		sp.WriteLine(cmd);
		sp.ReadLine(ans, sizeof(ans));

		if (strcmp(ans, M_ANS_ERROR) == 0)
		{
			sp.WriteLine(M_DO_CR);
			sp.ReadLine(ans, sizeof(ans));
			if (strcmp(ans, M_ANS_CC) != 0)
			{
				// TODO: Set errormsg somewhere
				throw MachineEvent(EVENT_MACHINE_ERROR, "Expected 'CC', recieved " + string(ans));
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

int MachineCommand::ExecCommandInt(SerialPort &sp, const char *cmd)
{
	char ans[5];
	int i;
	// TODO: Check for errors in write/ReadLine in sp.
	sp.WriteLine(cmd);
	sp.ReadLine(ans, sizeof(ans));
	if(EOF == sscanf_s(ans, "%d", &i))
	{
		return -1;
	}

	
	
	return i;
}