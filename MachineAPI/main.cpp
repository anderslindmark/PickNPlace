#include <iostream>
#include "MachineController.h"
#include "MachineCommand.h"

using namespace std;

void main() {
	MachineCommand test;
	MachineController mc("hej");
	bool test2 = mc.runCommand(  *(new MachineCommand())  );
	cout << endl<<"first " <<test2<<endl;
	test2 = mc.runCommand(  *(new MachineCommand())  );
	cout << endl<<"second " <<test2<<endl;
	mc.wait();
	test2 = mc.runCommand(  *(new MachineCommand())  );
	cout << endl<<"third " <<test2<<endl;
	mc.wait();
	//cout << "TEST : " << test2  << endl;
}