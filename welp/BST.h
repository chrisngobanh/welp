#ifndef BST_H_
#define BST_H_

#include <cstddef>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

//An object can have multiple ways to compare itself
template <class bstvalue, class bstobj>
class BST
{
private:
    struct Node
    {
        bstvalue value;
		bstobj obj;
        Node* left;
        Node* right;

        Node(): left(NULL), right(NULL) {}
		Node(bstvalue newvalue, bstobj newobj) : left(NULL), right(NULL), value(newvalue), obj(newobj) {}
    };

    typedef struct Node* Nodeptr;

    Nodeptr root;
    int size;

    /**Private helper functions*/

    void addValue(Nodeptr root, bstvalue value, bstobj obj);
    void inOrderPrint(Nodeptr root);
    void preOrderPrint(Nodeptr root);
    void postOrderPrint(Nodeptr root);
    void inOrderPrint(Nodeptr root, bstvalue min, bstvalue max);
    void preOrderPrint(Nodeptr root, bstvalue min, bstvalue max);
    void postOrderPrint(Nodeptr root, bstvalue min, bstvalue max);
    void inOrderVector(Nodeptr root, vector<bstobj> &list);
    void inOrderVector(Nodeptr root, bstvalue min, bstvalue max, vector<bstobj> &list);
    void deleteTree(Nodeptr root);
    bool containsValue(Nodeptr root, bstvalue value, bstobj obj);
    bstobj findMin(Nodeptr root);

public:
    BST();
    ~BST();
    bool isEmpty();
    int getSize();
    void add(bstvalue value, bstobj obj);
    bstobj getRoot();
    void printInOrder();
    void printPreOrder();
    void printPostOrder();
    void printInOrder(bstvalue min, bstvalue max);
    void printPreOrder(bstvalue min, bstvalue max);
    void printPostOrder(bstvalue min, bstvalue max);
    void getVectorInOrder(vector<bstobj> &list);
    void getVectorInOrder(bstvalue min, bstvalue max, vector<bstobj> &list);
    bool contains(bstvalue value);
    bstobj minimum();

};




/**Private helper functions*/

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::addValue(Nodeptr root, bstvalue value, bstobj obj)
{
    if (value <= root->value)
    {
        if (root->left != NULL) addValue(root->left, value, obj);
        else
        {
            root->left = new Node(value, obj);
            size++;
        }
    }
    else
    {
        if (root->right != NULL) addValue(root->right, value, obj);
        else
        {
            root->right = new Node(value, obj);
            size++;
        }
    };
}

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::inOrderPrint(Nodeptr root)
{
    if (root != NULL)
    {
        inOrderPrint(root->left);
        cout << root->obj << "\n";
        inOrderPrint(root->right);
    }
}

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::preOrderPrint(Nodeptr root)
{
    if (root != NULL)
    {
        cout << root->value << " ";
        preOrderPrint(root->left);
        preOrderPrint(root->right);
    }
}

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::postOrderPrint(Nodeptr root)
{
    if (root != NULL)
    {
        postOrderPrint(root->left);
        postOrderPrint(root->right);
        cout << root->value << " ";
    }
}

//--------------------------------------

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::inOrderPrint(Nodeptr root, bstvalue min, bstvalue max)
{
    if (root != NULL)
    {
        inOrderPrint(root->left, min, max);
        if (root->value >= min && root->value <= max) cout << root->value << " ";
        inOrderPrint(root->right, min, max);
    }
}

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::preOrderPrint(Nodeptr root, bstvalue min, bstvalue max)
{
    if (root != NULL)
    {
        if (root->value >= min && root->value <= max) cout << root->value << " ";
        preOrderPrint(root->left, min, max);
        preOrderPrint(root->right, min, max);
    }
}

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::postOrderPrint(Nodeptr root, bstvalue min, bstvalue max)
{
    if (root != NULL)
    {
        postOrderPrint(root->left, min, max);
        postOrderPrint(root->right, min, max);
        if (root->value >= min && root->value <= max) cout << root->value << " ";
    }
}

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::inOrderVector(Nodeptr root, vector<bstobj> &list)
{
    if (root != NULL)
    {
        inOrderVector(root->left, list);
        list.insert(list.begin(), root->obj);
        inOrderVector(root->right, list);
    }
}

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::inOrderVector(Nodeptr root, bstvalue min, bstvalue max, vector<bstobj> &list)
{
    if (root != NULL)
    {
        inOrderVector(root->left, min, max, list);
		if (root->value >= min && root->value <= max) list.insert(list.begin(), root->obj);
        inOrderVector(root->right, min, max, list);
    }
}

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::deleteTree(Nodeptr root)
{
    if (root != NULL)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

template <class bstvalue, class bstobj>
bool BST<bstvalue, bstobj>::containsValue(Nodeptr root, bstvalue value, bstobj obj)
{
    if (root != NULL)
    {
        if (value == root->value) return true;
        else if (value < root->value) return containsValue(root->left, value, obj);
        else return containsValue(root->right, value, obj);
    }
    return false;
}

template <class bstvalue, class bstobj>
bstobj BST<bstvalue, bstobj>::findMin(Nodeptr root)
{
    if (root != NULL)
    {
        if (root->left != NULL) return findMin(root->left);
        else return root->obj;
    }
}


/**Public functions*/

template <class bstvalue, class bstobj>
BST<bstvalue, bstobj>::BST()
{
    root = NULL;
    size = 0;
}

template <class bstvalue, class bstobj>
BST<bstvalue, bstobj>::~BST()
{
    deleteTree(root);
}

template <class bstvalue, class bstobj>
bool BST<bstvalue, bstobj>::isEmpty()
{
    return root == NULL;
}

template <class bstvalue, class bstobj>
int BST<bstvalue, bstobj>::getSize()
{
    return size;
}

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::add(bstvalue value, bstobj obj)
{
    if (root == NULL)
    {
        root = new Node(value, obj); //if the tree is empty insert the value at the root
        size++;
    }
    else addValue(root, value, obj); //otherwise call the helper function, passing it the root
}

template <class bstvalue, class bstobj>
bstobj BST<bstvalue, bstobj>::getRoot()
{
    if (root == NULL)
    {
        cout << "Error: The tree is empty." << endl << endl;
        exit(-1); // what to do if bstdata is a non reference like string?
    }
    else return root->obj;
}

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::printInOrder()
{
    if (isEmpty()) cout << "Error: The tree is empty." << endl << endl;
    else inOrderPrint(root);
}

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::printPreOrder()
{
    if (isEmpty()) cout << "Error: The tree is empty." << endl << endl;
    else preOrderPrint(root);
}

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::printPostOrder()
{
    if (isEmpty()) cout << "Error: The tree is empty." << endl << endl;
    else postOrderPrint(root);
}

//------------------------------------------------

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::printInOrder(bstvalue min, bstvalue max)
{
    if (isEmpty()) cout << "Error: The tree is empty." << endl << endl;
    else inOrderPrint(root, min, max);
}

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::printPreOrder(bstvalue min, bstvalue max)
{
    if (isEmpty()) cout << "Error: The tree is empty." << endl << endl;
    else preOrderPrint(root, min, max);
}

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::printPostOrder(bstvalue min, bstvalue max)
{
    if (isEmpty()) cout << "Error: The tree is empty." << endl << endl;
    else postOrderPrint(root, min, max);
}

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::getVectorInOrder(vector<bstobj> &list)
{
    if (isEmpty()) cout << "Error: The tree is empty." << endl << endl;
    else inOrderVector(root, list);
}

template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::getVectorInOrder(bstvalue min, bstvalue max, vector<bstobj> &list)
{
    if (isEmpty()) cout << "Error: The tree is empty." << endl << endl;
    else inOrderVector(root, min, max, list);
}

template <class bstvalue, class bstobj>
bool BST<bstvalue, bstobj>::contains(bstvalue value)
{
    if (isEmpty()) return false;
    if (value == root->data) return true;
    else return containsValue(root, value);
}

template <class bstvalue, class bstobj>
bstobj BST<bstvalue, bstobj>::minimum()
{
    if (root->value == NULL)
    {
        cout << "Minimum: Tree is empty" << endl;
        //will need to include cstdlib for exit below
        exit(-1); //you can also use assert here if desired
    }
    else
    {
        return findMin(root);
    }

}

#endif
