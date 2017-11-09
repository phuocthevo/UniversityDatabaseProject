// Binary Search Tree ADT: to use as data structure for stock database
// The structure is used mainly for storing data in ordered list by name and symbol
// Created by Frank M. Carrano and Tim Henry.
// Modified by: HUY DUC VO

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE
#include "BinaryTree.h"
enum key { FIRSTKEY, SECONDKEY }; // FIRST KEY = CODE ; SECOND KEY = NAME
template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{

public:
	// insert a node at the correct location
	bool insert(const ItemType & newEntry, char key);


	// remove a node if found
	bool remove(const ItemType & anEntry, char key);


	// find a target node
	bool getEntry(const ItemType & anEntry, ItemType & returnedItem, char key, void visit(ItemType &)) const;

private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode, char key);


	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success, char key);


	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);

	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target, char key, void visit(ItemType &), bool& success) const;

};


///////////////////////// public function definitions ///////////////////////////
/**************************************************** /
/*insert function*/
/*****************************************************/
template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry, char key)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = this->_insert(this->rootPtr, newNodePtr, key);
	this->count++;
	return true;
}

/**************************************************** /
/*remove function*/
/*****************************************************/
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target, char key)
{
	bool isSuccessful = false;
	this->rootPtr = this->_remove(this->rootPtr, target, isSuccessful, key);
	if (isSuccessful)
		this->count--;
	return isSuccessful;
}


/**************************************************** /
/*getEntry function*/
/*****************************************************/
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem, char key, void visit(ItemType &)) const
{
	bool success = false;
	BinaryNode<ItemType>* ptr = findNode(this->rootPtr, anEntry, key, visit, success);
	if (success == true && key == SECONDKEY)
	{
		return success;
	}
	if (success != true && key == SECONDKEY)
		return false;
	if (ptr) {
		returnedItem = ptr->getItem();
		success = true;
	}
	return success;
}

// *****************************************
//  findNode function
// *****************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
	const ItemType & target, char key, void visit(ItemType &), bool& success) const
{
	BinaryNode<ItemType>* findPtr = nodePtr;
	if (findPtr == NULL)
		return findPtr;
	if (key == FIRSTKEY)
	{
		if (*(findPtr->getItem()) == *target)
			return findPtr;
		if (*(findPtr->getItem()) > *target)
			findPtr = findNode(findPtr->getLeftPtr(), target, key, visit, success);
		else
			findPtr = findNode(findPtr->getRightPtr(), target, key, visit, success);

	}
	if (key != FIRSTKEY)
	{
		ItemType item = nodePtr->getItem();
		if (*target % *item) {
			visit(item);
			success = true;
		}
		findNode(nodePtr->getLeftPtr(), target, key, visit, success);
		findNode(nodePtr->getRightPtr(), target, key, visit, success);
	}
	return findPtr;
}


//////////////////////////// private functions ////////////////////////////////////////////
// *****************************************
//  _insert function
// *****************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
	BinaryNode<ItemType>* newNodePtr, char key)
{
	if (!nodePtr) {
		nodePtr = newNodePtr;
		return nodePtr;
	}
	if (key == FIRSTKEY) {
		if (*(nodePtr->getItem()) > *(newNodePtr->getItem()))
		{
			nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr, key));
		}
		else
		{
			nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr, key));
		}
		return nodePtr;
	}
	if (key == SECONDKEY) {
		if (*(nodePtr->getItem()) >= *(newNodePtr->getItem()))
			nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr, key));
		else
			nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr, key));
		return nodePtr;
	}
	return 0;
}

// *****************************************
//  _remove function
// *****************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
	const ItemType target, bool & success, char key)

{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (key == FIRSTKEY) {
		if ((*nodePtr->getItem()) > *target)
			nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success, key));
		else if ((*nodePtr->getItem()) < *target)
			nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success, key));
		else if ((*nodePtr->getItem()) == *target)
		{
			nodePtr = deleteNode(nodePtr);
			success = true;
		}
		return nodePtr;
	}
	if (key == SECONDKEY)
	{
		if ((*nodePtr->getItem()) >= *target)
			nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success, key));
		else if ((*nodePtr->getItem()) <= *target)
			nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success, key));
		else if ((*nodePtr->getItem()) != *target)
		{
			nodePtr = deleteNode(nodePtr);
			success = true;
		}
		return nodePtr;
	}
}


// *****************************************
//  deleteNode function
// *****************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}

// *****************************************
//  removeLeftmostNode function
// *****************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
	ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}

#endif
