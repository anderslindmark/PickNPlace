#include <iostream>
#include "MachineController.h"
#include "TestCommand.h"

using namespace std;

void main() {
	MachineController mc("hej");
	bool test2 = mc.runCommand(  *(new TestCommand())  );
	cout << endl<<"first " <<test2<<endl;
	test2 = mc.runCommand(  *(new TestCommand())  );
	cout << endl<<"second " <<test2<<endl;
	mc.wait();
	test2 = mc.runCommand(  *(new TestCommand())  );
	cout << endl<<"third " <<test2<<endl;
	mc.wait();
	//cout << "TEST : " << test2  << endl;
}