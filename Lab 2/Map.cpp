#include "Map.h"
#include "MapIterator.h"

Map::Map() {
	this->head = NULL;
	this->tail = NULL;
	this->nrElems = 0;
}

Map::~Map() {
	DLLNode* currentNode = this->head;
	DLLNode* nextNode;
	while (currentNode != NULL)
	{
		nextNode = currentNode->next;
		delete currentNode;
		currentNode = nextNode;
	}
}

//BC: theta(1)
//WC: theta(n)
//AC: theta(n)
//Total complexity: O(n)
TValue Map::add(TKey c, TValue v){
	
	if (this->head == NULL)          //if the list is empty, we initialise the head and the tail with the new node
	{
		DLLNode* newNode = new DLLNode;
		newNode->next = NULL;
		newNode->prev = NULL;
		newNode->info = TElem(c, v);
		this->head = newNode;
		this->tail = newNode;
		this->nrElems++;
		return NULL_TVALUE;
	}
	
	DLLNode* currentNode = this->head;  //searching for the key in the list
	while (currentNode != NULL)
	{
		if (currentNode->info.first == c)  //if the key already exist in the list, we just change its value
		{
			TValue oldValue = currentNode->info.second;
			currentNode->info = TElem(c, v);
			return oldValue;
		}
		currentNode = currentNode->next;
	}

	DLLNode* newNode = new DLLNode;  //if it does not exist in the list, we create a new node and insert it at the end
	newNode->info = TElem(c, v);
	newNode->next = NULL;
	newNode->prev = this->tail;
	this->tail->next = newNode;
	this->tail = newNode;
	this->nrElems++;
	return NULL_TVALUE;
}

//BC: theta(1)
//WC: theta(n)
//AC: theta(n)
//Total complexity: O(n)
TValue Map::search(TKey c) const{
	DLLNode* currentNode = this->head;
	while (currentNode != NULL)
	{
		if (currentNode->info.first == c)
		{
			return currentNode->info.second;
		}
		currentNode = currentNode->next;
	}
	return NULL_TVALUE;
}

//BC: theta(1)
//WC: theta(n)
//AC: theta(n)
//Total complexity: O(n)
TValue Map::remove(TKey c){
	DLLNode* currentNode = this->head;
	while (currentNode != NULL)
	{
		if (currentNode->info.first == c)
			break;
		currentNode = currentNode->next;
	} // finding the position of the node that we have to delete
	if (currentNode == NULL)
		return NULL_TVALUE;
	TValue deletedValue = currentNode->info.second;
	if (currentNode == this->head) //if we have to remove the first element
		if (currentNode == this->tail) //the list has one single element which is both the head and the tail
		{
			this->head = NULL;
			this->tail = NULL;
		}
		else //we have to remove the first element from a list with more than 1 elements
		{
			this->head = this->head->next;
			this->head->prev = NULL;
		}
	else if (currentNode == this->tail) //we have to remove the last element (the tail) of a list with >1 elements
	{
		this->tail = this->tail->prev;
		this->tail->next = NULL;
	}
	else
	{
		currentNode->prev->next = currentNode->next;
		currentNode->next->prev = currentNode->prev;
	}
	delete currentNode;
	this->nrElems--;
	return deletedValue;
}

//theta(1)
int Map::size() const {

	return this->nrElems;
}

//theta(1)
bool Map::isEmpty() const{
	if (this->head == NULL)
		return true;
	return false;
}

//theta(1)
MapIterator Map::iterator() const {
	return MapIterator(*this);
}

// BC: one of the lists is empty => theta(1)
// WC: when no key from Map m is in this map => theta(n*m), where n and m are the sizes of the two lists
// AC: theta(n*m)
// Total Complexity: O(n*m)
int Map::updateValues(Map& m)
{
	int nrOfModifiedPairs = 0;
	if (this->head == NULL)   //if one of the list is empty, no pair will be modified
		return 0;
	if (m.size() == 0)
		return 0;

	DLLNode* currentNode = m.head;   //currentNode will parse the nodes from Map m
	while (currentNode != NULL)
	{
		TKey currentKey = currentNode->info.first;
		DLLNode* currentNodeInMyMap = this->head;     //currentNodeInMyMap will parse the nodes from this map
		while (currentNodeInMyMap != NULL)
		{
			if (currentNodeInMyMap->info.first == currentKey)   //if the node from this map has the same key as the node
																//from Map m, we change its value and increase nr of modified pairs
			{
				currentNodeInMyMap->info.second = currentNode->info.second;
				nrOfModifiedPairs++;
				break;
			}
			currentNodeInMyMap = currentNodeInMyMap->next;
		}
		currentNode = currentNode->next;
	}
	return nrOfModifiedPairs;
}



