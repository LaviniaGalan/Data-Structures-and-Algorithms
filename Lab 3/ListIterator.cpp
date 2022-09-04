#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>


ListIterator::ListIterator(const IndexedList& list) : list(list){
    this->currentPosition = list.head;
}

//BC = WC = AC
//theta(1)
void ListIterator::first(){
    this->currentPosition = list.head;
}

//BC = WC = AC
//theta(1)
void ListIterator::next(){
    if (this->valid() == false)
        throw std::exception();
    this->currentPosition = list.nodes[this->currentPosition].next;
}

//BC = WC = AC
//theta(1)
bool ListIterator::valid() const{
    if (this->currentPosition == -1)
	    return false;
    return true;
}

//BC = WC = AC
//theta(1)
TElem ListIterator::getCurrent() const{
    if (this->valid() == false)
        throw std::exception();
    return list.nodes[this->currentPosition].info;
}

// BC: when the current position of the iterator is already -1 (invalid) => theta(1)
// WC: when the current position is the head => theta(min(n,k))
// AC: the average of the all possible cases => theta(min(n,k))
// Total Complexity: O(min(n,k))

void ListIterator::jumpForward(int k)
{
    if (k <= 0)
        throw std::exception("The number of steps must be strictly positive!");
    int nr = 1;
    while (nr <= k && this->currentPosition != -1)
    {
        this->currentPosition = list.nodes[this->currentPosition].next;
        nr++;
    }
    if (nr < k && this->valid() == false)
        throw std::exception("There aren't k elements left in the list.");
}
