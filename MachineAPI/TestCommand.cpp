#include "TestCommand.h"

TestCommand::TestCommand(string in)
{
	my = in;
}

TestCommand::~TestCommand(void)
{
}

string TestCommand::getCommand() {
	return my;
}
