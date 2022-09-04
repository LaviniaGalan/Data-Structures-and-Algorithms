#include <exception>

#include "IndexedList.h"
#include "ListIterator.h"

//theta(n), where n is the capacity
//BC = WC = AC
IndexedList::IndexedList() {
    this->head = -1;
    this->tail = -1;
    this->capacity = 10;
    this->nrElems = 0;

    this->nodes = new DLLANode[this->capacity];
    for (int i = 0; i < this->capacity; i++)
    {
        this->nodes[i].prev = i - 1;
        this->nodes[i].next = i + 1;
    }
    this->nodes[this->capacity - 1].next = -1;
    this->firstEmpty = 0;
}

//theta(1)
//BC = WC = AC
int IndexedList::size() const {
    return this->nrElems;
}

//theta(1)
//BC = WC = AC
bool IndexedList::isEmpty() const {
    if (this->nrElems == 0)
        return true;
	return false;
}

//O(n)
//BC: the list is empty => theta(1)
//WC: the element is not in the list => theta(n)
//AC: theta(n)
int IndexedList::search(TElem e) const {
    int currentPos = this->head;
    int positionInList = 0;
    while (currentPos != -1 && this->nodes[currentPos].info != e)
    {
        currentPos = this->nodes[currentPos].next;
        positionInList++;
    }
    if (currentPos != -1)
        return positionInList;
    return -1;
}

//O(n)
//BC: theta(1)
//WC: theta(n)
//AC: theta(n)
TElem IndexedList::getElement(int pos) const {
    if (pos < 0)
        throw std::exception();
    int currentPos = 0;
    int currentNod = this->head;
    while (currentNod != -1 && currentPos != pos)
    {
        currentNod = this->nodes[currentNod].next;
        currentPos++;
    }
    if (currentNod == -1)
        throw std::exception();
    return this->nodes[currentNod].info;
}

//O(n)
//BC: theta(1)
//WC: theta(n)
//AC: theta(n)
TElem IndexedList::setElement(int pos, TElem e) {
    if (pos < 0)
        throw std::exception();
    int currentPos = 0;
    int currentNod = this->head;
    while (currentNod != -1 && currentPos != pos)
    {
        currentNod = this->nodes[currentNod].next;
        currentPos++;
    }
    if (currentNod == -1)
        throw std::exception();
    TElem oldValue = this->nodes[currentNod].info;
    this->nodes[currentNod].info = e;
    return oldValue;
}

//O(n)
//BC: theta(1)
//WC: theta(n)
//AC: theta(n)
void IndexedList::addToPosition(int pos, TElem e) {
    if (pos < 0 || pos > this->nrElems)
        throw std::exception();
    if (this->nrElems == this->capacity - 1)
    {
        //resize
        DLLANode* newNodes = new DLLANode[this->capacity * 2];
        for (int i = 0; i < this->capacity; i++)
        {
            newNodes[i].prev = this->nodes[i].prev;
            newNodes[i].next = this->nodes[i].next;
            newNodes[i].info = this->nodes[i].info;
        }

        for (int i = this->capacity; i < this->capacity * 2; i++)
        {
            newNodes[i].prev = i - 1;
            newNodes[i].next = i + 1;
        }
        newNodes[this->capacity * 2 - 1].next = -1;
        delete[] this->nodes;
        this->nodes = newNodes;
        this->firstEmpty = this->capacity;
        this->capacity *= 2;
    }
    //allocate new node
    int nodeToInsert = this->firstEmpty;
    if (nodeToInsert != -1)
    {
        this->firstEmpty = this->nodes[this->firstEmpty].next;
        this->nodes[nodeToInsert].info = e;
        if (this->firstEmpty != -1)
            this->nodes[this->firstEmpty].prev = -1;
        this->nodes[nodeToInsert].next = -1;
        this->nodes[nodeToInsert].prev = -1;
    }
        
    //add it to the right position
    this->nrElems++;
    if (pos == 0) //if we have to add it to begining, we must change the head
    {
        if (this->head == -1)   //if the list is empty, this new node is both the tail and the head
        {
            this->head = nodeToInsert;
            this->tail = nodeToInsert;
        }
        else   
        {
            this->nodes[nodeToInsert].next = this->head;
            this->nodes[this->head].prev = nodeToInsert;
            this->head = nodeToInsert;
        }
    }
    else
    {
        int currentPos = 0;
        int currentNode = this->head;
        while (currentNode != -1 && currentPos < pos - 1)  //searching for the position to insert
        {
            currentNode = this->nodes[currentNode].next;
            currentPos++;
        }
        if (currentNode != -1)            //if the position is valid
        {
            int nextNode = this->nodes[currentNode].next;
            this->nodes[nodeToInsert].next = nextNode;
            this->nodes[nodeToInsert].prev = currentNode;
            this->nodes[currentNode].next = nodeToInsert;
            if (nextNode == -1)
                this->tail = nodeToInsert;
            else
                this->nodes[nextNode].prev = nodeToInsert;
        }
    }
    
}

//O(n)
//BC: theta(1)
//WC: theta(n)
//AC: theta(n)
TElem IndexedList::remove(int pos) {
    if (pos < 0)
        throw std::exception();
    int currentPos = 0;
    int currentNod = this->head;
    while (currentNod != -1 && currentPos != pos)
    {
        currentNod = this->nodes[currentNod].next;
        currentPos++;
    }
    if (currentNod == -1)          // the position is not valid
        throw std::exception();
    TElem retValue = this->nodes[currentNod].info;  //if the position is valid, we remove the element and change the links and the firstEmpty
    if (currentNod == this->head)
    {
        if (currentNod == this->tail)   //if the list has only one node
        {
            this->firstEmpty = this->head;
            this->head = -1;
            this->tail = -1;
        }
        else
        {
            int aux = this->firstEmpty;
            this->firstEmpty = this->head;              //if we remove the head of a list with more than one element
            this->head = this->nodes[this->head].next;
            this->nodes[this->head].prev = -1;
            this->nodes[this->firstEmpty].next = aux;
        }
    }
    else if (currentNod == this->tail)
    {
        int aux = this->firstEmpty;
        this->firstEmpty = this->tail;
        this->tail = this->nodes[this->tail].prev;
        this->nodes[this->tail].next = -1;
        this->nodes[this->firstEmpty].next = aux;
    }
    else
    {
       
        int aux = this->firstEmpty;
        this->firstEmpty = currentNod;
        
        this->nodes[this->nodes[currentNod].prev].next = this->nodes[currentNod].next;
        this->nodes[this->nodes[currentNod].next].prev = this->nodes[currentNod].prev;
        this->nodes[this->firstEmpty].next = aux;
    }
    this->nrElems--;
    return retValue;
}

//theta(1) amortized
void IndexedList::addToEnd(TElem e) {
    if (this->nrElems == this->capacity - 1)
    {
        //resize
        DLLANode* newNodes = new DLLANode[this->capacity * 2];
        for (int i = 0; i < this->capacity; i++)
        {
            newNodes[i].prev = this->nodes[i].prev;
            newNodes[i].next = this->nodes[i].next;
            newNodes[i].info = this->nodes[i].info;
        }
        for (int i = this->capacity; i < this->capacity * 2; i++)
        {
            newNodes[i].prev = i - 1;
            newNodes[i].next = i + 1;
        }
        newNodes[this->capacity * 2 - 1].next = -1;
        delete[] this->nodes;
        this->nodes = newNodes;
        this->firstEmpty = this->capacity;
        this->capacity *= 2;
    }
    int nodeToInsert = this->firstEmpty;    //allocate new node for the added element
    if (this->firstEmpty != -1)
    {
        this->firstEmpty = this->nodes[this->firstEmpty].next;
        this->nodes[nodeToInsert].info = e;
        if (this->firstEmpty != -1)
            this->nodes[this->firstEmpty].prev = -1;
        this->nodes[nodeToInsert].next = -1;
    }

    if (this->head == -1)          //if the list is empty, we change the head
        this->head = nodeToInsert;
    else
    {
        this->nodes[this->tail].next = nodeToInsert;  //else, we set the links between the tail and the new node
        this->nodes[nodeToInsert].prev = this->tail;
    }

    this->tail = nodeToInsert;    //the new node becomes the tail
    this->nrElems++;
}

//theta(1)
//BC=WC=AC
ListIterator IndexedList::iterator() const {
    return ListIterator(*this);        
}

IndexedList::~IndexedList() {
    delete[] this->nodes;
}