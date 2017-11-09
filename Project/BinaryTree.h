// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: HUY DUC VO

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include <iomanip>
#include <iostream>
#include <functional>
#include "Queue.h"
using namespace std;


template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
	BinaryTree() { rootPtr = 0; count = 0; }
	BinaryTree(const BinaryTree<ItemType>* & tree){ rootPtr = copyTree(tree->rootPtr); count = tree->count; }
	virtual ~BinaryTree() { destroyTree(rootPtr); }
	BinaryTree & operator= (const BinaryTree & sourceTree);

	// common functions for all binary trees
	bool isEmpty() const	{ return count == 0; }
	int size() const	    { return count; }
	void clear()			{ destroyTree(rootPtr); rootPtr = 0; count = 0; }
	
	void inOrder(const function<void(ItemType&)>& visit) const  { _inorder(visit, rootPtr); }
	
	void breadthFirstTraverse(const function<void(ItemType&)>& visit);
	
	void printIndented(void visit(ItemType &,int lvl));

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData, char key) = 0;
	

	virtual bool remove(const ItemType & anEntry,char key) = 0;
	

	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem, char key, void visit(ItemType &)) const = 0;

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);
	void printIndentedList(void visit(ItemType &, int), BinaryNode<ItemType>* nodePtr, int level) const;

	// internal traverse
	
	void _inorder(const function<void(ItemType&)>& visit, BinaryNode<ItemType>* nodePtr) const;
	
};

//////////////////////////////////////////////////////////////////////////
// *****************************************
//  copyTree function
// *****************************************
template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
	if (!nodePtr) {
		return 0;
	}

	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>;

	newNodePtr->setItem(nodePtr->getItem());
	newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
	newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));

	return newNodePtr;
}

// *****************************************
//  destroyTree function
// *****************************************
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr){
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
	}
}

// *****************************************
//  breadthFirstTraverse function
// *****************************************
template <class ItemType>
void BinaryTree<ItemType>::breadthFirstTraverse(const function<void(ItemType&)>& visit){
	if (!rootPtr)
		return;
	Queue<BinaryNode<ItemType>*> queue;
	BinaryNode<ItemType>*front;
	queue.enqueue(rootPtr);
	while (!queue.isEmpty()){
		queue.queueFront(front);
		ItemType item = front->getItem();
		visit(item);
		if (front->getLeftPtr())
			queue.enqueue(front->getLeftPtr());
		if (front->getRightPtr())
			queue.enqueue(front->getRightPtr());
		queue.dequeue(front);
	}
}


// *****************************************
//  _inorder function
// *****************************************
template<class ItemType>
void BinaryTree<ItemType>::_inorder(const function<void(ItemType&)>& visit, BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0){
		ItemType item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

// *****************************************
//  operator= function
// *****************************************
template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
	destroyTree(rootPtr);
	rootPtr = NULL;
	count = 0;
	rootPtr = copyTree(sourceTree.rootPtr);

	return *this;
}
// *****************************************
//  printIndented function
// *****************************************
template <class ItemType>
void BinaryTree<ItemType>::printIndented(void visit(ItemType &, int lvl)){
	if (rootPtr)
		printIndentedList(visit, rootPtr, 1);
}

// *****************************************
//  printIndentedList function
// *****************************************
template <class ItemType>
void BinaryTree<ItemType>::printIndentedList(void visit(ItemType &, int), BinaryNode<ItemType>* nodePtr, int level) const {
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item, level);
		level += 1;
		printIndentedList(visit, nodePtr->getRightPtr(), level);
		printIndentedList(visit, nodePtr->getLeftPtr(), level);

	}
}


#endif