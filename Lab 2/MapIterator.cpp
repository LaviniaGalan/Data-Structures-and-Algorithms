#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	this->currentPtr = this->map.head;
}

//theta(1)
void MapIterator::first() {
	this->currentPtr = this->map.head;
}

//theta(1)
void MapIterator::next() {
	if (this->valid() == false)
		throw exception{ "" };
	this->currentPtr = this->currentPtr->next;
}

//theta(1)
TElem MapIterator::getCurrent(){
	if (this->valid() == false)
		throw exception{ "" };
	return this->currentPtr->info;
}

//theta(1)
bool MapIterator::valid() const {
	if (this->currentPtr == NULL)
		return false;
	return true;
}



