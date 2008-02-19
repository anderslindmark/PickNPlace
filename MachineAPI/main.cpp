#include <iostream>
#include "MachineController.h"
#include "TestCommand.h"

using namespace std;

string hehe() {
	string p = "piss";
	return p;
}

void main() {
	string test = "aaa";
	cout << test << endl << hehe() << endl;
	MachineController mc("hej");
	bool test2 = mc.runCommand(  *(new TestCommand("o23o"))  );
	cout << endl<<"first " <<test2<<endl;
	test2 = mc.runCommand(  *(new TestCommand("o45o"))  );
	cout << endl<<"second " <<test2<<endl;
	mc.wait();
	test2 = mc.runCommand(  *(new TestCommand("o78o"))  );
	cout << endl<<"third " <<test2<<endl;
	mc.wait();
	//cout << "TEST : " << test2  << endl;
}