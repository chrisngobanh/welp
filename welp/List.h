// Author(s): Chris, Kevin
// Doubly Linked List
#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

// Documentation is provided before the implementation of every function

template <class listitem>
class List
{

private:
	struct Node
	{
		listitem data;
		Node* next;
		Node* previous;

		Node() : next(NULL), previous(NULL) {} //define our own default constructor
		Node(listitem data) : next(NULL), previous(NULL), data(data){}
	};

	typedef struct Node* NodeRef;

	NodeRef head;
	NodeRef tail;
	NodeRef iterator; //points to one node at a time
	int size;
	string identifier; //so that the hash table knows when to stop looking

	void reverse(NodeRef node);

public:
	/**Constructors and Destructors*/

	List();
	//Default constructor; initializes and empty list
	//Postcondition: Size should be zero and the head, tail, and iterator should be pointing to NULL.

	~List();
	//Destructor. Frees memory allocated to the list
	//Postcondition: The iterator should be pointing to NULL.

	List(const List &list);
	//Copy construcor. Initializes list to have the same elements as another list
	//Postcondition: The size of the list should be the same as the size of the referenced list, and all of the elements of the list should have the same data as all of the elements in the referenced list including the head, tail, and iterator. If list is empty, the head, tail and iterator should be NULL. If the referenced list has their iterator off the end (NULL), then the iterator should be off the end as well

	/**Accessors*/

	listitem back();
	//Returns the last element in the list
	//Precondition: The list size cannot be 0.

	listitem current();
	//Returns the element pointed to by the iterator
	//Precondition: The list size cannot be 0 and iterator cannot be off the end.

	listitem front();
	//Returns the first element in the list
	//Precondition: The list size cannot be 0.

	bool empty();
	//Determines whether a list is empty.

	bool off_end();
	//Determines if the iterator is off the end of the list

	int get_size();
	//Returns the length of the list


	/**Manipulation Procedures*/

	void setIdentifier(string _identifier);
	//changes the identifier

	double getAverage();
	//gets the average of the list by casting listobj to an int

	void begin();
	//Moves the iterator to point to the first element in the list
	//If the list is empty, the iterator remains NULL
	//Postcondition: The iterator should be pointing to the first element in the list.

	void insert(listitem data);
	//Inserts a new element into the list in the position after the iterator
	//Precondition: Iterator can't be pointing at NULL
	//Postcondition: The inserted data should should match the data in the parameter.

	void push_back(listitem data);
	//Inserts a new element at the end of the list
	//If the list is empty, the new element becomes both head and tail
	//Postcondition: The tail data should match data in the parameter.

	void push_front(listitem data);
	//Inserts a new element at the front of the list
	//If the list is empty, the new element becomes both head and tail
	//Postcondition: The head data should match the data in the parameter.

	void pop_front();
	//Removes the value of the first element in the list
	//Precondition: Size of list can't be 0.

	void pop_back();
	//Removes the value of the last element in the list
	//Precondition: Size of list can't be 0 .

	void remove();
	//Removes the element pointed at by the iterator
	//causing iterator to go offEnd
	//Precondition: The iterator cannot be off the end.

	void scroll();
	//Moves the iterator forward by one element in the list
	//Has no effect if the iterator is offend or the list is empty

	bool scrollTo(listitem _data);
	//Moves the iterator to a node with matching data
	//Returns true if such a node exists

	/**Additional List Operations*/

	void print();
	//Prints to the console the value of each element in the list sequentially
	//and separated by a blank space
	//Prints nothing if the list is empty

	void printReverse();
	//Calls the reverse helper function to
	//Pre: !isEmpty()

    /**
     * String Cast
     * Author(s): Kevin
     *
     * Returns the identifier.
     * One of the ways that the List can be compared by
     */
	explicit operator const string()
	{
	    return identifier;
	};
	//string cast for use in the hash table to know when it gets the right List


};

/**
 * List Constructor
 * Author(s): Chris
 *
 * Creates a list. Sets the head, tail, and iterator to NULL;
 */
template <class listitem>
List<listitem>::List()
{
	size = 0;
	head = tail = iterator = NULL;
	identifier = "";

	if (size != 0)
	{
		cout << "Size of list was not properly initialized. Something went wrong." << endl;
		assert(size != 0);
	}

	if (head != NULL)
	{
		cout << "Head pointer not properly initialized. Something went wrong." << endl;
		assert(head != NULL);
	}

	if (tail != NULL)
	{
		cout << "Tail pointer not properly initialized. Something went wrong." << endl;
		assert(tail != NULL);
	}

	if (iterator != NULL)
	{
		cout << "Iterator not properly initialized. Something went wrong." << endl;
		assert(iterator != NULL);
	}
}

/**
 * List Destructor
 * Author(s): Chris
 *
 * Frees up allocated memory. Loops through the list and deletes every node
 */
template <class listitem>
List<listitem>::~List()
{
	iterator = head;
	NodeRef temp;
	while (iterator != NULL)
	{
		temp = iterator;
		iterator = iterator->next;
		delete temp;
	}

	head = tail = NULL;

	if (iterator != NULL)
	{
		cout << "Iterator not pointing to NULL. Something went wrong." << endl;
		assert(iterator != NULL);
	}
}

/**
 * List Copy Constructor
 * Author(s): Chris
 *
 * Creates a deep copy of a list.
 */
template <class listitem>
List<listitem>::List(const List &list) : size(list.size)
{
	if (list.head == NULL) //If the original list is empty, make an empty list for this list
	{
		head = tail = iterator = NULL;
	}
	else
	{

		head = new Node(list.head->data);

		NodeRef temp1 = list.head;
		NodeRef temp2 = head; // To hold previous node
		iterator = head;

		while (temp1->next != NULL)
		{
			temp2 = iterator;
			temp1 = temp1->next;
			iterator->next = new Node(temp1->data);
			iterator = iterator->next;
			iterator->previous = temp2;
		}

		tail = iterator;

		// Make the iterators match
		if (list.iterator == NULL)
		{
			iterator = NULL;
		}
		else
		{
			while (iterator->data != list.iterator->data)
			{
				iterator = iterator->previous;
			}

		}
	}

	if (size != list.size)
	{
		cout << "Size of list does not match the size of the referenced list. Something went wrong." << endl;
		assert(size != list.size);
	}

	if (head->data != list.head->data)
	{
		cout << "Data in the head of list does not match the data in the head of the referenced list. Something went wrong." << endl;
		assert(head->data != list.head->data);
	}

	if (tail->data != list.tail->data)
	{
		cout << "Data in the tail of list does not match the data in the tail of the referenced list. Something went wrong." << endl;
		assert(tail->data != list.tail->data);
	}

	// If either one of the iterators is NULL
	if (iterator == NULL || list.iterator == NULL)
	{
		// If one of the iterators is not NULL
		if (iterator != list.iterator)
		{
			cout << "Iterators do not match." << endl;
			assert(iterator == list.iterator);
		}
	}
	else if (iterator->data != list.iterator->data)
	{
		cout << "Data in the iterators do not match. Something went wrong." << endl;
		assert(head->data != list.head->data);
	}

}

/**
 * Back
 * Author(s): Chris
 *
 * Returns the last object inside the list
 * Pre: The tail is not NULL
 */
template <class listitem>
listitem List<listitem>::back()
{
	if (size == 0)
	{
		cout << "Cannot get last element because list is empty." << endl;
		assert(size == 0);
	}

	return tail->data;
}

/**
 * Current
 * Author(s): Chris
 *
 * Returns the object that the iterator currently is pointing at
 * Pre: The iterator is pointing at something not NULL
 */
template <class listitem>
listitem List<listitem>::current()
{
	if (size == 0)
	{
		cout << "Cannot get element pointed at by iterator because list is empty." << endl;
		assert(size == 0);
	}

	if (iterator == NULL)
	{
		cout << "Cannot get element pointed at by iterator because iterator is off the end." << endl;
		assert(iterator == NULL);
	}

	return iterator->data;
}

/**
 * Front
 * Author(s): Chris
 *
 * Returns the first object in the list
 * Pre: The head is not NULL
 */
template <class listitem>
listitem List<listitem>::front()
{

	if (size == 0)
	{
		cout << "Cannot get first element because list is empty." << endl;
		assert(size == 0);
	}

	return head->data;
}

/**
 * Empty
 * Author(s): Chris
 *
 * Checks if the list is empty or not
 * Returns true if it is
 */
template <class listitem>
bool List<listitem>::empty()
{
	return (size == 0);
}

/**
 * Off End
 * Author(s): Chris
 *
 * Checks if the iterator is pointing to NULL
 * Returns true if the iterator is pointing to NULL
 */
template <class listitem>
bool List<listitem>::off_end()
{
	return (iterator == NULL);
}

/**
 * Get Size
 * Author(s): Chris
 *
 * Returns the length of the list
 */
template <class listitem>
int List<listitem>::get_size()
{
	return size;
}

/**
 * Begin
 * Author(s): Chris
 *
 * Makes the iterator point to the head
 */
template <class listitem>
void List<listitem>::begin()
{
	if (size == 0)
	{
		cout << "List is empty!" << endl;
		return;
	}

	iterator = head;

	if (iterator != head)
	{
		cout << "Iterator should be pointing at head. Something went wrong." << endl;
	}
}

/**
 * Insert
 * Author(s): Chris
 *
 * Inserts an object after the iterator
 * Pre: Iterator is not NULL
 */
template <class listitem>
void List<listitem>::insert(listitem data)
{
	if (iterator == NULL)
	{
		cout << "Iterator is currently off the end, can't insert the data." << endl;
	}
    else if (iterator == tail)
    {
        push_back(data);
    }
	else
	{
		NodeRef newNode = new Node(data);
		newNode->previous = iterator;
		newNode->next = iterator->next;

		iterator->next = newNode;
		newNode->next->previous = newNode;
		size++;
	}

	if (iterator->next->data != data) {
		cout << "The inserted data doesn't match the data that was passed. Something went wrong." << endl;
	}
}

/**
 * Push Back
 * Author(s): Chris
 *
 * Adds an object to the end of the list. The tail is the new object
 */
template <class listitem>
void List<listitem>::push_back(listitem data)
{
	if (size == 0)
	{
		tail = head = new Node(data);
	}
	else
	{
		NodeRef newNode = new Node(data);
		newNode->previous = tail;
		tail->next = newNode;
		tail = newNode;
	}

	size++;

	if (tail->data != data)
	{
		cout << "Data in the tail doesn't match the data that was password. Something went wrong." << endl;
	}
}

/**
 * Push Front
 * Author(s): Chris
 *
 * Adds an object to the front of the list. The head is the new object
 */
template <class listitem>
void List<listitem>::push_front(listitem data)
{
	if (size == 0)
	{
		head = tail = new Node(data);
	}
	else
	{
		NodeRef newNode = new Node(data);
		newNode->next = head;
		head->previous = newNode;
		head = newNode;
	}

	size++;

	if (head->data != data)
	{
		cout << "Data in the head doesn't match the data that was password. Something went wrong." << endl;
	}

}

/**
 * Pop Front
 * Author(s): Chris
 *
 * Deletes the object at the front. The object after the head is the new head
 */
template <class listitem>
void List<listitem>::pop_front()
{
	if (size == 0) //or make a call to the empty() function
	{
		cout << "Cannot pop front on an empty list." << endl;
	}
	else if (size == 1)
	{
		delete head;
		head = tail = iterator = NULL;
		size = 0;
	}
	else
	{
		if (iterator == head)
		{
			iterator = head->next; // If iterator is currently at the head, move it to head->next (the new head)
		}

		NodeRef temp = head;
		head = head->next;
		head->previous = NULL;

		delete temp;
		size--;


	}
}

/**
 * Empty
 * Author(s): Chris
 *
 * Deletes an object at the end of the list. The object before the tail is the new tail
 */
template <class listitem>
void List<listitem>::pop_back()
{
	if (size == 0) //or make a call to the empty() function
	{
		cout << "Cannot pop back on an empty list." << endl;
	}
	else if (size == 1)
	{
		delete tail;
		tail = head = iterator = NULL;
		size = 0;
	}
	else
	{
		if (iterator == tail)
		{
			iterator = tail->previous; // If iterator is currently at the tail, move it to tail->next (the new tail)
		}

		NodeRef temp = tail;
		tail = tail->previous;
		tail->next = NULL;
		delete temp;

		size--;
	}
}

/**
 * Remove
 * Author(s): Chris
 *
 * Deletes the object that is currently pointed at by the iterator
 * Pre: Iterator is pointing at an object
 */
template <class listitem>
void List<listitem>::remove()
{
	if (iterator == NULL)
	{
		cout << "Iterator is currently off the end, can't remove anything." << endl;
	}
	else
	{
		if (iterator == head)
		{
			head = head->next;
			delete iterator;
			head->previous = iterator = NULL;
		}
		else if (iterator == tail)
		{
			tail = tail->previous;
			delete iterator;
			tail->next = iterator = NULL;
		}
		else
		{
			iterator->previous->next = iterator->next;
			iterator->next->previous = iterator->previous;
			delete iterator;
			iterator = NULL;
		}
		size--;
	}
}

/**
 * Scroll
 * Author(s): Chris
 *
 * Iterates the iterator
 */
template <class listitem>
void List<listitem>::scroll()
{
	if ((iterator != NULL))
	{
		iterator = iterator->next;
	}
}

/**
 * Scroll To
 * Author(s): Kevin
 *
 * Moves the iterator to a given object
 * Returns true if the object was found
 */
template <class listitem>
bool List<listitem>::scrollTo(listitem _data)
{
    iterator = head;
    while (iterator != NULL && iterator->data != _data)
    {
        iterator = iterator->next;
    }
    return (iterator != NULL);
}

/**
 * Print
 * Author(s): Chris
 *
 * Prints the list forwards, from head to tail
 */
template <class listitem>
void List<listitem>::print()
{
	NodeRef temp = head;
	while (temp != NULL) {
		cout << temp->data << endl << endl;
		temp = temp->next;
	}
}

/**
 * Print Reverse
 * Author(s): Chris
 *
 * Prints the list backwards, from tail to head
 */
template <class listitem>
void List<listitem>::printReverse()
{
	reverse(tail);
}

/**
 * Reverse
 * Author(s): Chris
 *
 * Helper function to printReverse
 * Used to print the list backwards, from tail to head
 */
template <class listitem>
void List<listitem>::reverse(NodeRef node)
{
	if (node != NULL) {
		cout << node->data << " ";
		reverse(node->previous);
	}
}

/**
 * Set Identifier
 * Author(s): Kevin
 *
 * Sets the identifier of the list.
 * The identifier is used when the list
 * is (string) cast
 */
template <class listitem>
void List<listitem>::setIdentifier(string _identifier)
{
	identifier = _identifier;
}

/**
 * Get Average
 * Author(s): Kevin
 *
 * Returns the average of all values inside the list
 * Pre: The objects inside the list can be (int) cast
 */
template <class listitem>
double List<listitem>::getAverage()
{
    double sum = 0;
    iterator = head;
    while (iterator != NULL)
    {
        sum = sum + (int)(iterator->data);
        iterator = iterator->next;
    }
    return sum/size;
}

#endif
