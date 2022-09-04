#include "ShortTest.h"
#include <assert.h>
#include "Map.h"
#include "MapIterator.h"


void testAll() { //call each function to see if it is implemented
	Map m;
	assert(m.isEmpty() == true);
	assert(m.size() == 0); //add elements
	assert(m.add(5,5)==NULL_TVALUE);
	assert(m.add(1,111)==NULL_TVALUE);
	assert(m.add(10,110)==NULL_TVALUE);
	assert(m.add(7,7)==NULL_TVALUE);
	assert(m.add(1,1)==111);
	assert(m.add(10,10)==110);
	assert(m.add(-3,-3)==NULL_TVALUE);
	assert(m.size() == 5);
	assert(m.search(10) == 10);
	assert(m.search(16) == NULL_TVALUE);
	assert(m.remove(1) == 1);
	assert(m.remove(6) == NULL_TVALUE);
	assert(m.size() == 4);


	TElem e;
	MapIterator id = m.iterator();
	id.first();
	int s1 = 0, s2 = 0;
	while (id.valid()) {
		e = id.getCurrent();
		s1 += e.first;
		s2 += e.second;
		id.next();
	}
	assert(s1 == 19);
	assert(s2 == 19);

}


void testUpdateValues()
{
	Map m1;
	m1.add(1, 4);
	m1.add(2, 5);
	m1.add(3, 6);
	m1.add(4, 7);

	Map m2;
	assert(m2.updateValues(m1) == 0);

	m2.add(1, 8);
	m2.add(10, 2);
	m2.add(4, 9);

	assert(m2.updateValues(m1) == 2);

	assert(m2.search(1) == 4);
	assert(m2.search(10) == 2);
	assert(m2.search(4) == 7);
}