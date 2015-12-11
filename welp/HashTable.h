#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include "List.h"
#include "MaxHeap.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <climits>

using namespace std;

template <class hashobj>
class HashTable {

public:
    HashTable();

    ~HashTable();
    //Will write as part of Lab 6

    int hash(string key, string identifier);
    //returns the hash of the key. Uses base + jump
    //until it finds the right one.

    int baseHash(string key, string identifier);
    //returns the base hash value for the given keys
    //the hash value is the sum of
    //the ASCII values of each character % the table size

    int jumpHash(int key);
    //use this hash if there's a collision
    //add base + jump until you find either NULL or the data you're looking for

    void addItem(string key, string identifier, hashobj _data);
    //inserts a new item into the table
    // calls the hash function on the key title to determine the correct bucket
    //if the item already exists it is replaced with the newer entry

    bool removeItem(string key, string identifier, hashobj _data);
    //removes the item with the given key
    //returns true if successful

    bool indexIsFilled(int index);
    bool indexIsFilled(string key, string identifier);
    //Returns true if the linked list at that index is not empty

    void printTable();
    //prints every review inside the table

    void printBucket(int index);
    void printBucket(string key, string identifier);
    //Prints the reviews of a single car

    double getAverageRatingBucket(int index);
    double getAverageRatingBucket(string key, string identifier);
    //Gets the average rating of a car

    List<hashobj>& getValue(string key, string identifier);
    //Gets the list object at the index

    int getNumAccesses(string key, string identifier);
    //A test for efficiency. Returns the number of checks in order to find a key's value
    int getTableSize();
    //A getter to help test the efficiency

    int getTotalNumObjects();
    //Gets the number of objects inside all the lists

    int getNumObjects(string key, string identifier);
    //Gets the number of objects stored at an index

	void clearIndex(string key, string identifier);
	//Makes the list at that index empty

	hashobj getFront(string key, string identifier);
	hashobj getFront(int index);
	//Returns the element at the front of the list at that index

	bool isInTable(string key, string identifier, hashobj _data);
	//Returns true if the object is found

	string getMax();
	//returns the object at the front of listSizeHeap

private:

    static const int TABLE_SIZE = 48;
    List<hashobj> Table[TABLE_SIZE];
    int numObjects;

    MaxHeap<int, string> listSizeHeap;
    //to show which list is the biggest
};

/**
 * HashTable Constructor
 * Author(s): Kevin
 *
 * Initializes the constructor. A List is created at every index.
 */
template <class hashobj>
HashTable<hashobj>::HashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        List<hashobj> list = List<hashobj>();
        Table[i] = list;
    }
    numObjects = 0;
    listSizeHeap = MaxHeap<int, string>(26);

}

/**
 * HashTable Destructor
 * Author(s): Kevin
 *
 * Nothing is ever made with new
 */
template <class hashobj>
HashTable<hashobj>::~HashTable()
{

}

/**
 * Hash
 * Author(s): Kevin
 *
 * Returns the index for a given key.
 * Jumps until it finds the object or empty index
 */
template <class hashobj>
int HashTable<hashobj>::hash(string key, string identifier)
{
    int index = baseHash(key, identifier);
	int jump = jumpHash(index);

	string name = "";
	name.append(key);
	name.append(" ");
	name.append(identifier);

	while ((string)Table[index] != name && indexIsFilled(index))
	{
		index = (index + jump) % TABLE_SIZE;
	}

	return index;
}

/**
 * Base Hash
 * Author(s): Kevin
 *
 * Calculates the base hash of an object based off its key.
 */
template <class hashobj>
int HashTable<hashobj>::baseHash(string key, string identifier)
{
    int index = 0;

    //Add the values of each char together
    for (int i = 0; i < key.length(); i++)
    {
        index = index + key[i];
    }

    for (int i = 0; i < identifier.length(); i++)
    {
        index = index + identifier[i];
    }
    return index % TABLE_SIZE;
}

/**
 * Jump Hash
 * Author(s): Kevin
 *
 * Calculates how much to jump by so as to resolve collisions
 */
template <class hashobj>
int HashTable<hashobj>::jumpHash(int key)
{
    //Prevents the jump hash being 0
    //which prevents infinite loops
    return 7 - (key % 7);
}

/**
 * Clear Index
 * Author(s): Kevin
 *
 * Empties the list at a given index
 */
template <class hashobj>
void HashTable<hashobj>::clearIndex(string key, string identifier)
{
	int index = hash(key, identifier);

	while (!Table[index].empty())
	{
		Table[index].pop_back();
		numObjects--;
	}
}

/**
 * Get Max
 * Author(s): Kevin
 *
 * Returns the longest list casted to a string
 */
template <class hashobj>
string HashTable<hashobj>::getMax()
{
    return listSizeHeap.getMaxObject();
}

/**
 * Get Front
 * Author(s): Kevin
 *
 * Returns the object at the front of a list at a given index
 */
template <class hashobj>
hashobj HashTable<hashobj>::getFront(string key, string identifier)
{
	int index = hash(key, identifier);

	Table[index].begin();

	return Table[index].current();
}

/**
 * Get Front
 * Author(s): Kevin
 *
 * Overloaded function from above
 */
template <class hashobj>
hashobj HashTable<hashobj>::getFront(int index)
{
	Table[index].begin();

	return Table[index].current();
}

/**
 * Get Total Number of Objects
 * Author(s): Kevin
 *
 * Returns the total number of objects inside the Table
 */
template <class hashobj>
int HashTable<hashobj>::getTotalNumObjects()
{
    return numObjects;
}

/**
 * Get Number of Objects
 * Author(s): Kevin
 *
 * Returns the total number of objects of a List at a given index
 */
template <class hashobj>
int HashTable<hashobj>::getNumObjects(string key, string identifier)
{
    int index = hash(key, identifier);
    return Table[index].get_size();
}

/**
 * Get Table Size
 * Author(s): Kevin
 *
 * Returns the Table Size
 */
template <class hashobj>
int HashTable<hashobj>::getTableSize()
{
    return TABLE_SIZE;
}

/**
 * Add Item
 * Author(s): Kevin
 *
 * Adds an object to a List in the Table
 */
template <class hashobj>
void HashTable<hashobj>::addItem(string key, string identifier, hashobj _data)
{
    //Calculate the index
    int index = hash(key, identifier);

    //If there's a review with the same user replace it
    //Otherwise just add it to the list
    if (Table[index].scrollTo(_data))
    {
        Table[index].insert(_data);
        Table[index].remove();
    }
	else
	{
	    string name = "";
	    name.append(key);
	    name.append(" ");
	    name.append(identifier);

	    if (Table[index].empty())
        {
            Table[index].setIdentifier(name);
            listSizeHeap.addObject(name, Table[index].get_size());
        }
		Table[index].push_back(_data);
		listSizeHeap.iterateValue(name, 1);
		numObjects++;

	}

}

/**
 * Index Is Filled
 * Author(s): Kevin
 *
 * Checks if an index is empty or not.
 * Returns true if it is not empty.
 */
template <class hashobj>
bool HashTable<hashobj>::indexIsFilled(int index)
{
    return !(Table[index].empty());
}

/**
 * Index Is Filled
 * Author(s): Kevin
 *
 * Same as above, overloaded function
 */
template <class hashobj>
bool HashTable<hashobj>::indexIsFilled(string key, string identifier)
{
    int index = hash(key, identifier);

    return !(Table[index].empty());
}

/**
 * Print Table
 * Author(s): Kevin
 *
 * Prints every object in the table. Debugging purposes mainly
 */
template <class hashobj>
void HashTable<hashobj>::printTable()
{
    cout << "Showing all reviews:" << endl << endl;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Table[i].print();
        if (!Table[i].empty()) cout << endl;
    }
}

/**
 * Print Bucket
 * Author(s): Kevin
 *
 * Prints every object at a given index.
 */
template <class hashobj>
void HashTable<hashobj>::printBucket(int index)
{
    Table[index].print();
}

/**
 * Print Bucket
 * Author(s): Kevin
 *
 * Same function as above, overloaded
 */
template <class hashobj>
void HashTable<hashobj>::printBucket(string key, string identifier)
{
    int index = hash(key, identifier);

    Table[index].print();
}

/**
 * Remove Item
 * Author(s): Kevin
 *
 * This function takes a string and checks if it can be converted to an int
 * Returns true if the string can be an int, and false if the string cannot be an int
 */
template <class hashobj>
bool HashTable<hashobj>::removeItem(string key, string identifier, hashobj _data)
{
    //Calculate the index
    int index = hash(key, identifier);

    //If the data is found in the list, delete it
    if (Table[index].scrollTo(_data))
    {
        string name = "";
	    name.append(key);
	    name.append(" ");
	    name.append(identifier);
	    listSizeHeap.iterateValue(name, -1);

        Table[index].remove();
        numObjects--;

        return true;
    }

    return false;
}

/**
 * Get Average Rating Bucket
 * Author(s): Kevin
 *
 * Returns the average (int) values of each object in a list.
 * Pre: Objects in the list have an (int) cast
 */
template <class hashobj>
double HashTable<hashobj>::getAverageRatingBucket(int index)
{
    if (indexIsFilled(index))
    {
        return Table[index].getAverage();
    }
    else return 0.0;
}

/**
 * Get Average Rating Bucket
 * Author(s): Kevin
 *
 * Same function as above, just overloaded
 */
template <class hashobj>
double HashTable<hashobj>::getAverageRatingBucket(string key, string identifier)
{
    int index = hash(key, identifier);

    return getAverageRatingBucket(index);
}

/**
 * Get Value
 * Author(s): Kevin
 *
 * Returns a list at a given index.
 * Shouldn't really be used
 */
template <class hashobj>
List<hashobj>& HashTable<hashobj>::getValue(string key, string identifier)
{
    int index = hash(key, identifier);

    return Table[index];
}

/**
 * Get Number Accesses
 * Author(s): Kevin
 *
 * Helper function to test efficiency.
 * Returns the amount of times it is needed to jump before finding an object.
 */
template <class hashobj>
int HashTable<hashobj>::getNumAccesses(string key, string identifier)
{
    string name = "";
	name.append(key);
	name.append(" ");
	name.append(identifier);

    int accesses = 1;
    int index = baseHash(key, identifier);
    int jump = jumpHash(index);
    while ( (string)Table[index] != name && indexIsFilled(index) )
    {
        index = (index + jump) % TABLE_SIZE;
        accesses++;
    }
    return accesses;
}

/**
 * Is In Table
 * Author(s): Kevin
 *
 * Checks if an object is in the table.
 * Returns true if it is found.
 */
template <class hashobj>
bool HashTable<hashobj>::isInTable(string key, string identifier, hashobj _data)
{
	//Calculate the index
	int index = hash(key, identifier);

	//If the data is found in the list, delete it
	if (Table[index].scrollTo(_data)) return true;

	return false;
}

#endif /* HASHTABLE_H_ */
