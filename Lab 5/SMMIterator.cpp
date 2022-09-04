#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>

// BC = WC = AC => theta(m) (given by the first() function)
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	this->arrayIt = new Node * [this->map.m];
	this->currentMin = nullptr;
	this->currentMinIndex = -1;
	this->first();
}

// BC = WC = AC => theta(m)
void SMMIterator::first(){
	this->currentMin = nullptr;
	for (int i = 0; i < this->map.m; i++)
	{
		this->arrayIt[i] = this->map.array[i];
		if (this->arrayIt[i] != nullptr)
		{
			if (this->currentMin == nullptr)
			{
				this->currentMinIndex = i;
				this->currentMin = this->arrayIt[i];
			}
			else
				if (this->currentMin != nullptr && this->map.rel(this->arrayIt[i]->info.first, currentMin->info.first) == true)
				{
					this->currentMinIndex = i;
					this->currentMin = this->arrayIt[i];
				}
		}
		
	}
}


//BC: the next element in the list at the position currentMinPos has the same key as the current minimum => theta(1)
//WC: we have to search for a new minimum key => theta(m)
//AC: the average of all possible cases => theta(m)
//Total complexity: O(m)
void SMMIterator::next() {

	if (this->valid() == false)
		throw exception("");

	TKey oldMinKey = this->currentMin->info.first;
	this->arrayIt[this->currentMinIndex] = this->arrayIt[this->currentMinIndex]->next;
	if (this->arrayIt[this->currentMinIndex] != nullptr && this->arrayIt[this->currentMinIndex]->info.first == oldMinKey)
	{
		this->currentMin = this->arrayIt[this->currentMinIndex];
		return;
	}
	this->currentMinIndex = -1;
	this->currentMin = nullptr;
	for (int i = 0; i < this->map.m; i++)
	{
		if (this->arrayIt[i] != nullptr)
		{
			if (this->currentMin == nullptr)
			{
				this->currentMinIndex = i;
				this->currentMin = this->arrayIt[i];
			}
				
			else if (this->map.rel(this->arrayIt[i]->info.first, this->arrayIt[this->currentMinIndex]->info.first) == true)
			{
				this->currentMinIndex = i;
				this->currentMin = this->arrayIt[i];
			}
		}
	}
}

//BC = WC = AC => theta(1)
bool SMMIterator::valid() const{
	if (this->currentMin == nullptr)
		return false;
	return true;
}

//BC = WC = AC => theta(1)
TElem SMMIterator::getCurrent() const{
	if (this->valid() == false)
		throw exception("");
	return this->currentMin->info;
}


