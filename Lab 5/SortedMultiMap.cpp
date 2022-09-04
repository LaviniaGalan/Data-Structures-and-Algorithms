#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

//BC = WC = AC => theta (1)
int SortedMultiMap::hash(TKey c) const
{
	return abs(c % this->m);
}

//BC = WC = AC => theta(m)
SortedMultiMap::SortedMultiMap(Relation r) {
	this->rel = r;
	this->m = 13;
	this->nrElems = 0;
	this->array = new Node * [this->m];
	for (int i = 0; i < this->m; i++)
	{
		this->array[i] = nullptr;
	}
	this->loadFactor = 0.7;
}


//BC = when we have to add at the begining of the list at the position given by the hash function => theta(1)
//WC = when we have to resize => theta (n^2)
//Total complexity: O(n^2)
void SortedMultiMap::add(TKey c, TValue v) {
	if (((float) this->nrElems / (float) this->m) > this->loadFactor)
	{
		this->resize();
	}

	int addPosition = this->hash(c);
	Node* addedNode = new Node;
	addedNode->info = TElem(c, v);
	addedNode->next = nullptr;

	Node* head = this->array[addPosition];

	if (head == nullptr)      //if the list at "hashed" position is empty
		this->array[addPosition] = addedNode;
	else
	{
		if (this->rel(c, head->info.first) == true)
			//if the relation is true, we add the node at the begining
		{
			addedNode->next = this->array[addPosition];
			this->array[addPosition] = addedNode;
		}
		else //we find the right position to insert the node
		{
			Node* currentNode = this->array[addPosition];
			Node* prevNode = nullptr;
			while (currentNode != nullptr && this->rel(c, currentNode->info.first) == false)
			{
				prevNode = currentNode;
				currentNode = currentNode->next;
			}
			prevNode->next = addedNode;
			addedNode->next = currentNode;
		}
	}
	this->nrElems++;

}



// BC: there is only one pair containing the key c and it is placed at the begining of the list at the position given by the hash function => theta(1)
// WC: there are no pairs with key c/the pairs having key c are the last from the list at the position given by the hash function => theta(n), where n are the number of pairs at the hashed position
// AC: the average of the all possible cases => theta(n)
// Total complexity: O(n), where n = the number of elements in the list at the hashed position 

vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> values;
	int position = this->hash(c);
	Node* currentNode = this->array[position];
	while (currentNode != nullptr && currentNode->info.first != c)  // moving forward in the list at the found position until we find the key c or until we reach the end of the list
	{
		currentNode = currentNode->next;
	}
	if (currentNode != nullptr)  // it means that we found a pair which contains the key c
	{
		Node* currentNodeWithKey = currentNode;
		while (currentNodeWithKey != nullptr && currentNodeWithKey->info.first == c)
		{
			values.push_back(currentNodeWithKey->info.second);
			currentNodeWithKey = currentNodeWithKey->next;
		}
			
	}
	return values;
}



// BC: the pair (c, v) is at the begining of the list at the position given by the hash function => theta(1)
// WC: the pair (c, v) is not in the list or it is the last from the list at the position given by the hash function => theta(n), where n are the number of pairs at the hashed position
// AC: the average of the all possible cases => theta(n)
// Total complexity: O(n), where n = the number of elements in the list at the hashed position 

bool SortedMultiMap::remove(TKey c, TValue v) {
	int position = this->hash(c);
	Node* head = this->array[position];
	if (head == nullptr)
		return false;      // if there is no element in the list corresponding to the hashed position

	Node* prevNode = nullptr;
	Node* currentNode = head;
	// finding the position of the first apparition of the key c in the list at hashed position
	while (currentNode != nullptr && currentNode->info.first != c)
	{
		prevNode = currentNode;
		currentNode = currentNode->next;
	}
		
	if (currentNode == nullptr)
		return false;

	// finding the position of the pair (c, v) in the list
	while (currentNode != nullptr && currentNode->info.first == c && currentNode->info.second != v)
	{
		prevNode = currentNode;
		currentNode = currentNode->next;
	}
		
	if (currentNode == nullptr || currentNode->info.first != c)
		return false;

	//if we reach this point, currentNode is the node we have to remove:
	if (currentNode == head)
	{
		this->array[position] = head->next;
	}
	else
	{
		prevNode->next = currentNode->next;
	}
	this->nrElems--;
	return true;
}


//BC = WC = AC => theta (1)
int SortedMultiMap::size() const {
	return this->nrElems;
}


//BC = WC = AC => theta (1)
bool SortedMultiMap::isEmpty() const {
	if (this->nrElems == 0)
		return true;
	return false;
}

//BC = WC = AC => theta (1)
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

//BC: all the elements are inserted at the begining of the list from their position => theta (2*m + n) ~ theta(m)
//WC: all elements are inserted in the same list, on the last position in the list => theta (n^2)
//AC: the average of all possible cases => theta(n^2)
//Total complexity: O(n^2)

void SortedMultiMap::resize()
{
	Node** newArray = new Node * [this->m * 2];

	for (int i = 0; i < this->m * 2; i++)
	{
		newArray[i] = nullptr;
	}
	this->m = this->m * 2;
	for (int i = 0; i < this->m / 2; i++)
	{
		Node* currentNode = this->array[i];

		while (currentNode != nullptr)
		{
			int addPosition = this->hash(currentNode->info.first);

			Node* addedNode = new Node;
			addedNode->info = TElem(currentNode->info.first, currentNode->info.second);
			addedNode->next = nullptr;

			Node* head = newArray[addPosition];

			if (head == nullptr)      //if the list at "hashed" position is empty
				newArray[addPosition] = addedNode;
			else
			{
				if (this->rel(currentNode->info.first, head->info.first) == true)
					//if the relation is true, we add the node at the begining
				{
					addedNode->next = newArray[addPosition];
					newArray[addPosition] = addedNode;
				}
				else //we find the right position to insert the node
				{
					Node* currentNodeInList = newArray[addPosition];
					Node* prevNode = nullptr;
					while (currentNodeInList != nullptr && this->rel(currentNode->info.first, currentNodeInList->info.first) == false)
					{
						prevNode = currentNodeInList;
						currentNodeInList = currentNodeInList->next;
					}
					prevNode->next = addedNode;
					addedNode->next = currentNodeInList;
				}
			}
			currentNode = currentNode->next;
		}
	}

	this->array = newArray;
}


//Given the fact that the load factor alpha = n/m is the average number of elements stored in a 
//chain, we have that at every step in the for loop, we check alpha numbers. 
//This means that we have, totally, alpha*m steps => BC = WC = AC = theta(m)

vector<TValue> SortedMultiMap::valueBag() const
{
	vector<TValue> values;
	for (int i = 0; i < this->m; i++)
	{
		Node* currentNode = this->array[i];
		while (currentNode != nullptr)
		{
			values.push_back(currentNode->info.second);
			currentNode = currentNode->next;
		}
	}
	return values;
}



//BC = WC = AC = theta(m)
SortedMultiMap::~SortedMultiMap() {

	Node* nextNode;
	for (int i = 0; i < this->m; i++)
	{
		Node* currentNode = this->array[i];
		while (currentNode != nullptr)
		{
			nextNode = currentNode->next;
			delete currentNode;
			currentNode = nextNode;
		}
	}
}