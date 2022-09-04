#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    testAll();
	testAllExtended();

	testNew();
    std::cout<<"Finished SMM Tests!"<<std::endl;
	system("pause");
}
