#include <assert.h>
#include "Matrix.h"
#include <iostream>
using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);
}

void testNew()
{
	//if the matrix is not a square matrix, throw exception
	Matrix invalidMatrix(5, 6);
	try
	{
		invalidMatrix.setMainDiagonal(1);
		assert(false);
	}
	catch (...)
	{
		assert(true);
	}
	
	Matrix m(8, 8);

	//adding some elements on main diagonal to check if they will be modified
	m.modify(0, 0, 3);
	m.modify(3, 3, 5);

	m.setMainDiagonal(10);
	//check if all the elements on main diagonal were modified
	for (int i = 0; i < m.nrLines(); i++)
	{
		assert(m.element(i, i) == 10);
	}

	m.setMainDiagonal(NULL_TELEM);
	//check if all the elements on main diagonal were removed
	for (int i = 0; i < m.nrLines(); i++)
	{
		assert(m.element(i, i) == NULL_TELEM);
	}
}