
#include "Settings.h"

#include <iostream>
using namespace std;

using namespace PicknPlaceGui;

int main(int argc, char *argv[])
{
    Settings s(QString("settings.xml"));
	if (!s.Read())
	{
		cout << "NO" <<s.errorString().toStdString() << endl;
	}
	s.SetFile(QString("settings2.xml"));
	s.Save();
	/*
	cout << "READ: "<< s.GetPNPSettings().offsetX << endl;
	cout << "READ: "<< s.GetPNPSettings().offsetY << endl;
	cout << "READ: "<< s.GetPNPSettings().headHeight << endl;
	cout << "READ: "<< s.GetPNPSettings().pickHeight << endl;
	cout << "READ: "<< s.GetPNPSettings().placeHeight << endl;
	cout << "READ: "<< s.GetPNPSettings().afterPickTime << endl;
	cout << "READ: "<< s.GetPNPSettings().pickPressDownTime << endl;
	cout << "READ: "<< s.GetPNPSettings().placePressDownTime << endl;
	cout << "READ: "<< s.GetPNPSettings().afterPlaceTime << endl << endl;

	cout << "READ: "<< s.GetDispenceSettings().offsetX << endl;
	cout << "READ: "<< s.GetDispenceSettings().offsetY << endl;
	cout << "READ: "<< s.GetDispenceSettings().offsetZ << endl;
	cout << "READ: "<< s.GetDispenceSettings().offsetZs << endl;
	cout << "READ: "<< s.GetDispenceSettings().offsetTurn << endl;
	cout << "READ: "<< s.GetDispenceSettings().speed << endl;
	cout << "READ: "<< s.GetDispenceSettings().beforeTime << endl;
	cout << "READ: "<< s.GetDispenceSettings().afterTime << endl;
	cout << "READ: "<< s.GetDispenceSettings().suckBackTime << endl;*/
	string tmp;
	cin >> tmp;
	return 0;
}


