#pragma once
#include "IndexedList.h"


class ListIterator{
    //DO NOT CHANGE THIS PART
	friend class IndexedList;
private:
	const IndexedList& list;
	
    

    ListIterator(const IndexedList& lista);
public:
    int currentPosition;
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;

    //moves the current element from the iterator k steps forward, or makes the iterator invalid if there are less than k elements left in the List.
//throws an exception if the iterator is invalid or if k is zero or negative
    void jumpForward(int k);

};

