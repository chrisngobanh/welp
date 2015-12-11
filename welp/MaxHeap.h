//Author: Kevin

#ifndef MAXHEAP_H
#define MAXHEAP_H
#include <iostream>

using std::cout;

// Documentation is provided before the implementation of every function


template <class heap_val, class heap_obj>
class MaxHeap
{
private:
    struct Node
    {
        heap_val value;
        heap_obj object;

        Node(){}
        Node(heap_val _value, heap_obj _object)
        {
            value = _value;
            object = _object;
        }
        heap_val getValue()
        {
            return value;
        }
        heap_obj getObject()
        {
            return object;
        }
    };

    int HEAP_SIZE;
    int numObjects;
    Node* Heap;

public:

    MaxHeap();
    // default constructor. doesn't do anything
    MaxHeap(int size);
    // alt constructor. Makes an array with size size
    ~MaxHeap();
    //destructor

    heap_val getMaxValue();
    //gets the max value. Heap[1].value
    heap_obj getMaxObject();
    //gets the max object. Heap[1].object

    void iterateValue(heap_obj obj, heap_val count);
    //the value at obj will increase by count ex. value = value + count. heapify() is used for you already
    void replaceValue(heap_obj obj, heap_val value);
    //replaces the value of an obj with the new one. heapify is used for you already
    void addObject(heap_obj obj, heap_val value);
    //adds an object to the heap. if the max number of objects is reached nothing happens.
    //needs manual build() again after use
    //you can call this multiple times in a row before you build() for slight efficiency

    void heapify(int index);
    //swaps an index with its biggest child if its not the biggest
    void print();
    //prints objects in the heap (like a normal array)
    void printValue();
    //prints values of the objects in the heap (like a normal array)
    void build();
    //turns an existing array into a max heap

    int parent(int index);
    //gets the parent index
    int left(int index);
    //gets the left child index
    int right(int index);
    //gets the right child index

};


/**
 * Max Heap Constructor
 * Author(s): Kevin
 *
 * Default constructor. Never used
 */
template <class heap_val, class heap_obj>
MaxHeap<heap_val, heap_obj>::MaxHeap()
{

}

/**
 * Max Heap Constructor
 * Author(s): Kevin
 *
 * Overloaded constructor. Creates an array with the input size
 */
template <class heap_val, class heap_obj>
MaxHeap<heap_val, heap_obj>::MaxHeap(int size)
{
    HEAP_SIZE = size;
    Heap = new Node[HEAP_SIZE + 1];
    numObjects = 0;
}

/**
 * Max Heap Destructor
 * Author(s): Kevin
 *
 * Frees up allocated memory
 */
template <class heap_val, class heap_obj>
MaxHeap<heap_val, heap_obj>::~MaxHeap()
{
    delete []Heap;
}

/**
 * Get Max Value
 * Author(s): Kevin
 *
 * Returns the value of the the biggest object inside the Max Heap
 */
template <class heap_val, class heap_obj>
heap_val MaxHeap<heap_val, heap_obj>::getMaxValue()
{
    return Heap[1].value;
}

/**
 * Get Max Object
 * Author(s): Kevin
 *
 * Returns the object with the biggest value inside the Max Heap
 */
template <class heap_val, class heap_obj>
heap_obj MaxHeap<heap_val, heap_obj>::getMaxObject()
{
    return Heap[1].object;
}

/**
 * Iterate Value
 * Author(s): Kevin
 *
 * Iterates to the value of an object count times if it is found.
 * Ex. value = value + count;
 */
template <class heap_val, class heap_obj>
void MaxHeap<heap_val, heap_obj>::iterateValue(heap_obj obj, heap_val count)
{
    for (int i = 1; i <= HEAP_SIZE; i++)
    {
        if (obj == Heap[i].object)
        {
            Heap[i].value = Heap[i].value + count;
            heapify(i);
            return;
        }
    }
}

/**
 * Replace Value
 * Author(s): Kevin
 *
 * Replaces the value of an object with the new one
 */
template <class heap_val, class heap_obj>
void MaxHeap<heap_val, heap_obj>::replaceValue(heap_obj obj, heap_val value)
{
    for (int i = 1; i <= HEAP_SIZE; i++)
    {
        if (obj == Heap[i].object)
        {
            Heap[i].value = value;
            heapify(i);
            return;
        }
    }
}

/**
 * Add Object
 * Author(s): Kevin
 *
 * Adds an object to an empty slot if an empty slot exists
 * Otherwise does nothing
 * It is neccessary to use build() after this
 * because this method is meant to be called multiple times in a row.
 */
template <class heap_val, class heap_obj>
void MaxHeap<heap_val, heap_obj>::addObject(heap_obj obj, heap_val value)
{
    if (numObjects < HEAP_SIZE)
    {
        Heap[numObjects + 1] = Node(value, obj);
        numObjects++;
    }
}

/**
 * Heapify
 * Author(s): Kevin
 *
 * Restores a part of the array so that the parent is the biggest value
 *
 */
template <class heap_val, class heap_obj>
void MaxHeap<heap_val, heap_obj>::heapify(int index)
{
    int index_left = left(index);
    int index_right = right(index);
    int index_max = index;

    if (index_left <= numObjects && index_right <= numObjects )
    {
        if (Heap[index_left].value > Heap[index_right].value) index_max = index_left;
        else if (Heap[index_right].value >= Heap[index_left].value) index_max = index_right;
    }

    if (Heap[index_max].value > Heap[index].value)
    {
        Node temp = Heap[index];
        Heap[index] = Heap[index_max];
        Heap[index_max] = temp;
        heapify(index_max);
    }
}

/**
 * Parent
 * Author(s): Kevin
 *
 * Utility function that gets the index of the index's parent
 */
template <class heap_val, class heap_obj>
int MaxHeap<heap_val, heap_obj>::parent(int index)
{
    return index/2;
}

/**
 * Left
 * Author(s): Kevin
 *
 * Utility function that gets the index of the index's left child
 */
template <class heap_val, class heap_obj>
int MaxHeap<heap_val, heap_obj>::left(int index)
{
    return index*2;
}

/**
 * Right
 * Author(s): Kevin
 *
 * Utility function that gets the index of the index's right child
 */
template <class heap_val, class heap_obj>
int MaxHeap<heap_val, heap_obj>::right(int index)
{
    return index*2 + 1;
}

/**
 * Print
 * Author(s): Kevin
 *
 * Prints the Heap's objects as if it were a regular array
 */
template <class heap_val, class heap_obj>
void MaxHeap<heap_val, heap_obj>::print()
{
    for (int i = 1; i <= numObjects; i++)
    {
        cout << Heap[i].object << " ";
    }
}

/**
 * Print Value
 * Author(s): Kevin
 *
 * Prints the value of the Heap's objects as if it were a regular array
 */
template <class heap_val, class heap_obj>
void MaxHeap<heap_val, heap_obj>::printValue()
{
    for (int i = 1; i <= numObjects; i++)
    {
        cout << Heap[i].value << " ";
    }
}

/**
 * Build
 * Author(s): Kevin
 *
 * Turns a regular array into a Max Heap.
 * It is neccessary to use this after using addObject
 */
template <class heap_val, class heap_obj>
void MaxHeap<heap_val, heap_obj>::build()
{
    int index = parent(numObjects);
    for (int i = index; i >= 1; i--)
    {
        heapify(i);
    }
}


#endif // MAXHEAP_H
