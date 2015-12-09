// Authors(s): Chris, Kevin

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

template <class hashobj>
string HashTable<hashobj>::getMax()
{
    return listSizeHeap.getMaxObject();
}

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

template <class hashobj>
hashobj HashTable<hashobj>::getFront(string key, string identifier)
{
	int index = hash(key, identifier);

	Table[index].begin();

	return Table[index].current();
}

template <class hashobj>
hashobj HashTable<hashobj>::getFront(int index)
{
	Table[index].begin();

	return Table[index].current();
}

template <class hashobj>
int HashTable<hashobj>::getTotalNumObjects()
{
    return numObjects;
}

template <class hashobj>
int HashTable<hashobj>::getNumObjects(string key, string identifier)
{
    int index = hash(key, identifier);
    return Table[index].get_size();
}

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

template <class hashobj>
HashTable<hashobj>::~HashTable()
{

}

template <class hashobj>
int HashTable<hashobj>::getTableSize()
{
    return TABLE_SIZE;
}

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

template <class hashobj>
bool HashTable<hashobj>::indexIsFilled(int index)
{
    return !(Table[index].empty());
}

template <class hashobj>
bool HashTable<hashobj>::indexIsFilled(string key, string identifier)
{
    int index = hash(key, identifier);

    return !(Table[index].empty());
}

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

template <class hashobj>
int HashTable<hashobj>::jumpHash(int key)
{
    //Prevents the jump hash being 0
    //which prevents infinite loops
    return 7 - (key % 7);
}

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

template <class hashobj>
void HashTable<hashobj>::printBucket(int index)
{
    Table[index].print();
}

template <class hashobj>
void HashTable<hashobj>::printBucket(string key, string identifier)
{
    int index = hash(key, identifier);

    Table[index].print();
}

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

template <class hashobj>
double HashTable<hashobj>::getAverageRatingBucket(int index)
{
    if (indexIsFilled(index))
    {
        return Table[index].getAverage();
    }
    else return 0.0;
}

template <class hashobj>
double HashTable<hashobj>::getAverageRatingBucket(string key, string identifier)
{
    int index = hash(key, identifier);

    return getAverageRatingBucket(index);
}

template <class hashobj>
List<hashobj>& HashTable<hashobj>::getValue(string key, string identifier)
{
    int index = hash(key, identifier);

    return Table[index];
}

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
