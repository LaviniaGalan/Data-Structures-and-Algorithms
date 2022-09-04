#include "Matrix.h"
#include <exception>
using namespace std;

// BC = AC = WC => theta(1)
Matrix::Matrix(int nrLines, int nrCols) {
	   
	this->root = NULL;
	this->rows = nrLines;
	this->cols = nrCols;
}

// BC = AC = WC => theta(1)
int Matrix::nrLines() const {
	return this->rows;
}

// BC = AC = WC => theta(1)
int Matrix::nrColumns() const {
	return this->cols;
}

// BC: the node we search for is the root => theta(1)
// WC: the node we search for is a leaf from the last level of the tree or the node we search for is not in the tree but its place would be as a child of a leaf from the last level of the tree
// => theta(h), where h is the height of the tree
// Total complexity: O(h)
TElem Matrix::element(int i, int j) const {
	if (i < 0 || i >= this->rows || j < 0 || j >= this->cols)
	{
		throw exception("");
	}

	BTNode* currentNode = this->root;
	while (currentNode != NULL)
	{
		if (i * this->cols + j < currentNode->info.row * this->cols + currentNode->info.col)
			currentNode = currentNode->left;
		else if (i * this->cols + j > currentNode->info.row * this->cols + currentNode->info.col)
			currentNode = currentNode->right;
		else
			return currentNode->info.value;
	}

	if (currentNode == NULL)
		return NULL_TELEM;
}


// BC: the best case of add/remove => theta(1)
// WC: the worst case of add/remove => theta(h)
// *described below
// Total complexity: O(h)
TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 || i >= this->rows || j < 0 || j >= this->cols)
	{
		throw exception("");
	}
	TElem result; 

	if (e != NULL_TELEM)
		result = this->add(i, j, e);
	else
	{	
		result = this->remove(i, j);
	}
	return result;
}


// BC: the element must be inserted as the root => theta(1)
// WC: the element must be the child of a leaf from the last level of the three => theta(h)
// Total complexity: O(h)

TElem Matrix::add(int i, int j, TElem e)
{
	BTNode* currentNode = this->root;
	BTNode* prevNode = NULL;
	while (currentNode != NULL)
	{
		prevNode = currentNode;
		if (i * this->cols + j < currentNode->info.row * this->cols + currentNode->info.col)
			currentNode = currentNode->left;
		else if (i * this->cols + j > currentNode->info.row * this->cols + currentNode->info.col)
			currentNode = currentNode->right;
		else if(i * this->cols + j == currentNode->info.row * this->cols + currentNode->info.col)
		{
			// if we have equality, we replace the old value with the new one
			TElem oldValue = currentNode->info.value;
			currentNode->info.value = e;
			return oldValue;
		}
	}

	BTNode* newNode = this->initNode(i, j, e);
	if (prevNode == NULL) // the tree is empty
	{
		this->root = newNode;
	}
	else if (i * this->cols + j < prevNode->info.row * this->cols + prevNode->info.col)
	{
		prevNode->left = newNode;
		newNode->parent = prevNode;
	}
	else
	{
		prevNode->right = newNode;
		newNode->parent = prevNode;
	}
	return NULL_TELEM;

}

// BC = AC = WC => theta(1)
BTNode* Matrix::initNode(int i, int j, TElem e)
{
	BTNode* newNode = new BTNode;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;
	newNode->info.row = i;
	newNode->info.col = j;
	newNode->info.value = e;

	return newNode;
}


// BC: the node we have to remove has 0 or 1 child and it is the root => theta(1)
// WC: the node we have to remove is a leaf from the last level of the tree OR we have to remove a node with two children, whose 
// predecessor is on the last level if the tree => theta(h)
// Total complexity: O(h)
TElem Matrix::remove(int i, int j)
{
	BTNode* currentNode = this->root;
	TElem oldValue;
	while (currentNode != NULL)    //searching in BST for the node we have to remove
	{
		if (i * this->cols + j < currentNode->info.row * this->cols + currentNode->info.col)
			currentNode = currentNode->left;
		else if (i * this->cols + j > currentNode->info.row* this->cols + currentNode->info.col)
			currentNode = currentNode->right;
		else if (i * this->cols + j == currentNode->info.row * this->cols + currentNode->info.col)
		{
			oldValue = currentNode->info.value;
			break;
		}
	}

	if (currentNode == NULL)
	{
		return NULL_TELEM;
	}

	if (currentNode->left == NULL && currentNode->right == NULL) //the node we remove has no children
	{
		if (currentNode->parent == NULL) //removing the root of a BST which contains only the root
			this->root = NULL;
		else
			this->setParentChildLink(currentNode, NULL);
	}

	else if (currentNode->left != NULL && currentNode->right != NULL) //the node has two children
	{
		BTNode* maximum = this->getMaximumNode(currentNode->left); // we get the maximum node from the left subtree
		//and replace the current node with this maximum node
			
		currentNode->info = maximum->info;
		if (maximum->left == NULL)                        //delete the maximum node from it initial place
			this->setParentChildLink(maximum, NULL);  
		else if (maximum->left != NULL)
		{
			this->setParentChildLink(maximum, maximum->left);
		}
		delete maximum;
		return oldValue;
	}

	else //the node we remove has one child => we replace the node with its children
	{
		BTNode* child;
		if (currentNode->left != NULL)
			child = currentNode->left;
		else
			child = currentNode->right;           
		
		this->setParentChildLink(currentNode, child);  // we set the links between the parent of the node and the child of the node
		child->parent = currentNode->parent;
		if (currentNode->parent == NULL)
		{
			this->root = child;
		}
	}

	delete currentNode;
	return oldValue;
}


// BC = AC = WC => theta(1)
void Matrix::setParentChildLink(BTNode* node, BTNode* newChild)
{
	if (node == NULL || node->parent == NULL)
		return;

	BTNode* parent = node->parent;

	if (parent->left == node)
		{
			parent->left = newChild;
			return;
		}

	if (parent->right == node)
		{
			parent->right = newChild;
			return;
		}
	
}

// BC: start doesn't have a right child => theta(1)
// WC: all the nodes, except the leaves, in the subtree having the root = start have a right child => theta(h),
// where h = the height of the subtree having 'start' as root
// Total complexity: O(h)
BTNode* Matrix::getMaximumNode(BTNode* start)
{
	BTNode* currentNode = start;
	if (currentNode == NULL)
		return NULL;

	while (currentNode->right != NULL)
	{
		currentNode = currentNode->right;
	}

	return currentNode;
}


// Extra functionality:
// BC and WC are given by the complexities of function modify
// BC: for all elements on the main diagonal, we have best case for function modify => theta(1 * nrCols) = theta(nrCols)
// WC: for all the elements from the main diagonal, we have worst case for "modify" => theta(h * nrCols)
// Total complexity: O(h * nrCols)
void Matrix::setMainDiagonal(TElem elem)
{
	if (this->cols != this->rows)
		throw exception("");

	for (int i = 0; i < this->cols; i++)
	{
		this->modify(i, i, elem);
	}
}

