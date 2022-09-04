#include <assert.h>

#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <vector>
#include <iostream>
using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v= smm.search(1);
    assert(v.size()==2);
    v= smm.search(3);
    assert(v.size()==0);
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	it.next();
    }
    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());
}

void testNew()
{
    cout << "Testing new functionality...\n";

    SortedMultiMap smm = SortedMultiMap(relation1);
    vector<TValue> v;

    //when the multi map is empty, the vector with values is empty
    v = smm.valueBag();
    assert(v.size() == 0);

    //testing the function on elements at the same position
    smm.add(2, 3);
    smm.add(2, 4);
    smm.add(2, 5);

    v = smm.valueBag();
    assert(v.size() == 3);
    for (TValue value : v)
    {
        assert(value == 3 || value == 4 || value == 5);
    }

    //testing for elements on different positions

    smm.add(5, 1);
    smm.add(6, 2);
    smm.add(7, 3);

    v = smm.valueBag();
    assert(v.size() == 6);
    for (TValue value : v)
    {
        assert(value == 3 || value == 4 || value == 5 || value == 1 || value == 2);
    }
}