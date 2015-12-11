//Author: Kevin

#ifndef MAXHEAP_H
#define MAXHEAP_H
#include <iostream>

using std::cout;

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

template <class heap_val, class heap_obj>
MaxHeap<heap_val, heap_obj>::MaxHeap()
{

}

template <class heap_val, class heap_obj>
MaxHeap<heap_val, heap_obj>::MaxHeap(int size)
{
    HEAP_SIZE = size;
    Heap = new Node[HEAP_SIZE + 1];
    numObjects = 0;
}

template <class heap_val, class heap_obj>
MaxHeap<heap_val, heap_obj>::~MaxHeap()
{
    delete []Heap;
}

template <class heap_val, class heap_obj>
heap_val MaxHeap<heap_val, heap_obj>::getMaxValue()
{
    return Heap[1].value;
}

template <class heap_val, class heap_obj>
heap_obj MaxHeap<heap_val, heap_obj>::getMaxObject()
{
    return Heap[1].object;
}

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

template <class heap_val, class heap_obj>
void MaxHeap<heap_val, heap_obj>::addObject(heap_obj obj, heap_val value)
{
    if (numObjects < HEAP_SIZE)
    {
        Heap[numObjects + 1] = Node(value, obj);
        numObjects++;
    }
}

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

template <class heap_val, class heap_obj>
int MaxHeap<heap_val, heap_obj>::parent(int index)
{
    return index/2;
}

template <class heap_val, class heap_obj>
int MaxHeap<heap_val, heap_obj>::left(int index)
{
    return index*2;
}

template <class heap_val, class heap_obj>
int MaxHeap<heap_val, heap_obj>::right(int index)
{
    return index*2 + 1;
}

template <class heap_val, class heap_obj>
void MaxHeap<heap_val, heap_obj>::print()
{
    for (int i = 1; i <= numObjects; i++)
    {
        cout << Heap[i].object << " ";
    }
}

template <class heap_val, class heap_obj>
void MaxHeap<heap_val, heap_obj>::printValue()
{
    for (int i = 1; i <= numObjects; i++)
    {
        cout << Heap[i].value << " ";
    }
}

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
