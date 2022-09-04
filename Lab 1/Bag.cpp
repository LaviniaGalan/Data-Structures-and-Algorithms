#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

Bag::Bag() {
	this->nrElems = 0;
	this->capacity = 2;
	this->arr = new TElem[this->capacity];
	this->minElemOfArr = 0;
}

//O(n), BC = theta(1), WC = theta(n)
void Bag::add(TElem elem) {
	if (this->nrElems == 0)
	{
		this->minElemOfArr = elem;
		this->arr[0] = 1;
		this->nrElems = 1;
		return;
	}
	TElem maxElem = this->minElemOfArr + this->nrElems - 1;
	
	if (elem >= this->minElemOfArr && elem <= maxElem)
		this->arr[elem - this->minElemOfArr] += 1;

	else if (elem > maxElem)
	{
		this->capacity = elem - this->minElemOfArr + 1;
		TElem* newArr = new TElem[this->capacity];
		for (int i = 0; i < this->nrElems; i++)
			newArr[i] = this->arr[i];
		for (int i = this->nrElems; i < this->capacity; i++)
			newArr[i] = 0;
		newArr[this->capacity - 1] = 1;
		delete[] this->arr;
		this->arr = newArr;
		this->nrElems = elem - this->minElemOfArr + 1;
	}

	else if (elem < this->minElemOfArr)
	{
		int i = 1;
		this->capacity = maxElem - elem + 1;
		TElem* newArr = new TElem[this->capacity];
		TElem aux = elem;
		newArr[0] = 1;
		aux++;
		while (aux < this->minElemOfArr)
		{
			newArr[i] = 0;
			i++;
			aux++;
		}
		for (int j = this->minElemOfArr; j < this->minElemOfArr + this->nrElems; j++)
			newArr[i + j - this->minElemOfArr] = this->arr[j - this->minElemOfArr];
		delete[] this->arr;
		this->arr = newArr;
		this->nrElems = maxElem - elem +1;
		this->minElemOfArr = elem;
	}
}

//O(n), BC = theta(1), WC = theta(n)
bool Bag::remove(TElem elem) {
	if (this->nrElems == 0) return false;

	TElem maxElem = this->minElemOfArr + this->nrElems - 1;

	if (elem >= this->minElemOfArr && elem <= maxElem && this->arr[elem - this->minElemOfArr] > 0)
	{
		this->arr[elem - this->minElemOfArr] = this->arr[elem - this->minElemOfArr] - 1;
		
		while (this->nrElems > 0 && this->arr[this->nrElems - 1] == 0)
		{
			this->nrElems--;
		}
		int distance = 0;
		while (this->nrElems > 0 && this->arr[distance] == 0)
		{
			distance++;
			this->nrElems--;
			this->minElemOfArr++;
		}
		if (distance != 0)
			for (int i = 0; i < this->nrElems; i++)
				this->arr[i] = this->arr[i + distance];
		return true;
	}
	return false;
}

//theta(1)
bool Bag::search(TElem elem) const {
	if (elem >= this->minElemOfArr && elem <= this->minElemOfArr + this->nrElems - 1 && this->arr[elem - minElemOfArr] > 0)
		return true;
	return false; 
}

//theta(1)
int Bag::nrOccurrences(TElem elem) const {
	if (elem >= this->minElemOfArr && elem <= this->minElemOfArr + this->nrElems - 1)
		return this->arr[elem - minElemOfArr];
	return 0;
}

//theta(n), n = nrElems of the bag
int Bag::size() const {
	int sum = 0;
	for (int i = 0; i < this->nrElems; i++)
	{
		sum += this->arr[i];	
	}
	return sum;
}

//theta(1)
bool Bag::isEmpty() const {
	if (this->nrElems == 0)
		return true;
	return false;
}

void Bag::addOccurrences(int nr, TElem elem)
{
	if (nr < 0)
		throw std::exception("Invalid number of occurrences!");
	if (this->nrElems == 0)
	{
		this->minElemOfArr = elem;
		this->arr[0] = nr;
		this->nrElems = 1;
		return;
	}
	TElem maxElem = this->minElemOfArr + this->nrElems - 1;
	//if the element is already in the list, we modify its frequency
	if (elem >= this->minElemOfArr && elem <= maxElem)
		this->arr[elem - this->minElemOfArr] = nr;

	//if the element is greater than the maxim element, we add positions to the right for the numbers in the interval [maxElem, elem]
	else if (elem > maxElem)
	{
		this->capacity = elem - this->minElemOfArr + 1;
		TElem* newArr = new TElem[this->capacity];
		for (int i = 0; i < this->nrElems; i++)
			newArr[i] = this->arr[i];
		for (int i = this->nrElems; i < this->capacity; i++)
			newArr[i] = 0;
		newArr[this->capacity - 1] = nr;
		delete[] this->arr;
		this->arr = newArr;
		this->nrElems = elem - this->minElemOfArr + 1;
	}

	//if the element is lower than the minim one, we add positions to the left for the interval [elem, minElem]
	else if (elem < this->minElemOfArr)
	{
		int i = 1;
		this->capacity = maxElem - elem + 1;
		TElem* newArr = new TElem[this->capacity];
		TElem aux = elem;
		newArr[0] = nr;
		aux++;
		while (aux < this->minElemOfArr)
		{
			newArr[i] = 0;
			i++;
			aux++;
		}
		for (int j = this->minElemOfArr; j < this->minElemOfArr + this->nrElems; j++)
			newArr[i + j - this->minElemOfArr] = this->arr[j - this->minElemOfArr];
		delete[] this->arr;
		this->arr = newArr;
		this->nrElems = maxElem - elem + 1;
		this->minElemOfArr = elem;
	}

}// Best Case = when the array is empty or when the element is already in the list. In this case, we perform just some
//assignments, so the complexity is theta(1).
// Worst Case = when we have to resize the array. We have a for loop in which we assign values corresponding to the
//numbers in the interval [elem, maxElem] or [minElem, elem], so the complexity is theta(n), where n is the difference
//between the ends of the interval.
// AC = sum with I belongs to D from P(I)*E(I) = 1/n * sum (with i = 1,n) i = 1/n * n*(n+1)/2 = (n+1)/2 => average case
//complexity is theta(n).
//So the total complexity is O(n).

// theta(1)
BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	delete[] this->arr;
}

