#include "ExtendedTest.h"
#include "ShortTest.h"

#include "Map.h"

#include <iostream>
using namespace std;


int main() {
	testAll();
	testAllExtended();

	cout << "That's all!" << endl;

	cout << "Test for new functionality: ..." << endl;
	testUpdateValues();
	cout << "Done." << endl;

	system("pause");
	return 0;
}


