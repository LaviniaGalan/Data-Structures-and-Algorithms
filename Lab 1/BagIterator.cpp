#include <exception>
#include <iostream>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

//theta(1)
BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->currentPos = 0;
	this->currentFreq = 0;
}
//theta(1)
void BagIterator::first() {
	this->currentPos = 0;
	this->currentFreq = 0;
}
// O(n), n = nrElems of the bag, BC = theta(1), WC = theta(n)
void BagIterator::next() {
	
	if (this->valid() == false)
		throw runtime_error{ "" };
	this->currentFreq += 1;
	if (this->currentFreq == this->bag.arr[this->currentPos])
	{
		this->currentPos += 1;
		this->currentFreq = 0;
	}
	while (currentPos < this->bag.nrElems && this->bag.arr[currentPos] == 0)
		currentPos += 1;

}

//theta(1)
bool BagIterator::valid() const {
	if (this->currentPos == this->bag.nrElems)
		return false;
	return true;
}

//theta(1)
TElem BagIterator::getCurrent() const
{
	if (this->valid() == false) 
		throw runtime_error{ "" };
	return this->bag.minElemOfArr + this->currentPos;
}

