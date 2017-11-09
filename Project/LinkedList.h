// A class template for holding a linked list.
// The node type is also a class template.

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//*********************************************
// The ListNode class creates a type used to  *
// store a node of the linked list.           *
//*********************************************

template <class T>
class ListNode
{
public:
    T value;           // Node value
    ListNode<T> *next; // Pointer to the next node

    // Constructor
    ListNode (T nodeValue){ value = nodeValue; next = NULL;}
};

//*********************************************
// LinkedList class                           *
//*********************************************

template <class T>
class LinkedList
{
private:
    ListNode<T> *head;   // List head pointer
    int count;

public:
    // Constructor
    LinkedList(){ head = NULL; count = 0; }

   // Destructor
   ~LinkedList();

   void insertNode(T);
   T* search(T);
   bool Delete(T);
};

//**************************************************
// The insertNode function inserts a node with     *
// newValue copied to its value member.            *
//**************************************************

template <class T>
void LinkedList<T>::insertNode(T newValue)
{
    ListNode<T> *newNode;             // A new node
    ListNode<T> *nodePtr;             // To traverse the list
    ListNode<T> *previousNode = NULL; // The previous node

    newNode = new ListNode<T>(newValue); // Allocate a new node and store newValue there.
    nodePtr = head;                      // Position nodePtr at the head of list.
    previousNode = NULL;                 // Initialize previousNode to NULL.

    // Skip all nodes whose value is less than newValue.
    while (nodePtr != NULL && nodePtr->value < newValue)
    {
         previousNode = nodePtr;
         nodePtr = nodePtr->next;
    }

    // If the new node is to be the 1st in the list,
    // insert it before all other nodes.
    if (previousNode == NULL)
    {
        head = newNode;
    }
    else  // Otherwise insert after the previous node.
    {
        previousNode->next = newNode;
    }
    newNode->next = nodePtr;
    count++;
}



//***************************************************
// search in the list the value of parameter passed
// into function, return the pointer to that node
//***************************************************

template <class T>
T* LinkedList<T>::search(T value)
{
	ListNode<T>* h = head;

	if (head == 0)
		return NULL;

	while (h!= NULL && h->value != value)
		h = h->next;

	
	if (h == NULL)
		return NULL;
	else
		return &(h->value);
}

//****************************************************
// delete a node in the linkedlist which has the 
// same value with the parameter passed into 
// function
//***************************************************

template<class T>
bool LinkedList<T>::Delete(T value)
{

	// temporary variable which is useful for traverse
	ListNode<T> * h = head;
	ListNode<T> * previous = 0;

	// if head is NULL, return with false action
	if (head == 0)
		return false;

	// traverse
	while (h)
	{
		// if we reach out target node
		if (h->value == value)
		{
			if (h == head) // if head is our target node, free head and set it to 0
			{
				delete head;
				head = 0;
			}
			else   // our target node is in the middle of the list
			{
				previous->next = h->next;
				h->next = 0;
				delete h;
				h = 0;
			}

			return true;
		}

		//walk
		previous->next = h;
		h = h->next;

	}

	return false;

}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************

template <class T>
LinkedList<T>::~LinkedList()
{
   ListNode<T> *nodePtr;   // To traverse the list
   ListNode<T> *nextNode;  // To point to the next node

   // Position nodePtr at the head of the list.
   nodePtr = head;

   // While nodePtr is not at the end of the list...
   while (nodePtr != NULL)
   {
      // Save a pointer to the next node.
      nextNode = nodePtr->next;

      // Delete the current node.
      delete nodePtr;

      // Position nodePtr at the next node.
      nodePtr = nextNode;
   }
}
#endif
