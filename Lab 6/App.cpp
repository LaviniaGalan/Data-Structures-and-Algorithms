
#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

using namespace std;


int main() {


	testAll();
	testAllExtended();
	cout << "\nTest new functionality...\n";
	testNew();
	cout << "Test End" << endl;
	system("pause");
}