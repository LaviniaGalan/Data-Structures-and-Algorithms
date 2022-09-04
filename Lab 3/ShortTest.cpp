#include <assert.h>
#include <exception>
#include <iostream>
#include "ShortTest.h"
#include "IndexedList.h"
#include "ListIterator.h"




void testAll() {
    IndexedList list = IndexedList();
    assert(list.isEmpty());
    list.addToEnd(1);
    
    assert(list.size() == 1);
   
    list.addToPosition(0,2);
    assert(list.size() == 2);
    ListIterator it = list.iterator();
    assert(it.valid());
    it.next();
    assert(it.getCurrent() == 1);
    it.first();
    assert(it.getCurrent() == 2);
    assert(list.search(1) == 1);
    assert(list.setElement(1,3) == 1);
    assert(list.getElement(1) == 3);
    assert(list.remove(0) == 2);
    assert(list.size() == 1);
}

void testNew()
{
    std::cout << "Test for jumpForward: ... \n";
    IndexedList list = IndexedList();
    list.addToEnd(10);
    list.addToEnd(20);
    list.addToEnd(30);
    list.addToEnd(40);
    list.addToEnd(50);
    list.addToEnd(60);

    ListIterator it = list.iterator();
    //if the number of steps (k) is 0 or negative, throw exception:
    try
    {
        it.jumpForward(0);
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }

    //valid number of steps, move k steps forward:
    it.first();
    it.jumpForward(1);
    assert(it.getCurrent() == 20);

    it.jumpForward(3);
    assert(it.getCurrent() == 50);
    
    //the number of steps is greater than the number of elements left in the list, should throw exception:
    try
    {
        it.jumpForward(5);
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }

    std::cout << "Test is finished!\n";
    
}
