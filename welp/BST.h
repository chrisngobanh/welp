#ifndef BST_H_
#define BST_H_

#include <cstddef>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>

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
    bstobj findMax(Nodeptr root);
    void printLevelOrder(Nodeptr root);


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
    bstobj maximum();
    void levelOrderPrint();

};




/**Private helper functions*/

/**
 * Add Value
 * Author(s): Kevin
 *
 * Adds a value into the BST. Sorted by bstvalue.
 * Has the ability to add objects with the same bstvalue
 */
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

/**
 * In Order Print
 * Author(s): Kevin
 *
 * Helper function to print the nodes in order
 */
template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::inOrderPrint(Nodeptr root)
{
    if (root != NULL)
    {
        inOrderPrint(root->left);
        cout << root->obj << endl;
        inOrderPrint(root->right);
    }
}

/**
 * Pre Order Print
 * Author(s): Kevin
 *
 * Helper function to print the nodes in pre order
 */
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

/**
 * Post Order Print
 * Author(s): Kevin
 *
 * Helper function to print the nodes in post order
 */
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

/**
 * In Order Print
 * Author(s): Kevin
 *
 * Helper function to print the nodes in order
 * This function is overloaded to print only within a range between min and max
 */
template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::inOrderPrint(Nodeptr root, bstvalue min, bstvalue max)
{
    if (root != NULL)
    {
        if (root->obj > min) inOrderPrint(root->left, min, max);
        if (root->value >= min && root->value <= max) cout << root->obj << endl;
        if (root->obj < max) inOrderPrint(root->right, min, max);
    }
}

/**
 * Pre Order Print
 * Author(s): Kevin
 *
 * Helper function to print the nodes in pre order
 * This function is overloaded to print only within a range between min and max
 */
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

/**
 * Post Order Print
 * Author(s): Kevin
 *
 * Helper function to print the nodes in post order
 * This function is overloaded to print only within a range between min and max
 */
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

/**
 * In Order Vector
 * Author(s): Kevin
 *
 * Adds values into a vector in order.
 */
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

/**
 * Print Level Order
 * Author(s): Kevin
 *
 * Helper function.
 * Special print, shows the level of each object.
 * Uses a BFS algorithm
 */
template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::printLevelOrder(Nodeptr root)
{
    queue<Nodeptr> nodeQ;
    queue<int> levelQ;
    Nodeptr iter;
    int level = 0;

    nodeQ.push(root);
    levelQ.push(level);

    while (!nodeQ.empty())
    {
        iter = nodeQ.front();
        level = levelQ.front();

        if (iter != NULL)
        {
            for (int i = 0; i < level; i++)
            {
                cout << "--";
            }
            cout << iter->obj << endl;
            if (iter->left != NULL)
            {
                nodeQ.push(iter->left);
                levelQ.push(level + 1);
            }
            if (iter->right != NULL)
            {
                nodeQ.push(iter->right);
                levelQ.push(level + 1);
            }
        }
        nodeQ.pop();
        levelQ.pop();
    }
}


/**
 * In Order Vector
 * Author(s): Kevin
 *
 * Adds values into a vector in order.
 * This function is overloaded so it only adds values between min and max
 */
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


/**
 * Delete Tree
 * Author(s): Kevin
 *
 * Deletes a subtree starting at a given root
 */
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


/**
 * Contians Value
 * Author(s): Kevin
 *
 * Checks if a value can be found inside the tree.
 * If an object with that value is found, return true.
 */
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


/**
 * Find Min
 * Author(s): Kevin
 *
 * Helper function to find the minimum value in a BST
 */
template <class bstvalue, class bstobj>
bstobj BST<bstvalue, bstobj>::findMin(Nodeptr root)
{
    if (root->left == NULL)
    {
        return root->obj;
    }
    else
    {
        return findMin(root->left);
    }

}


/**
 * Find Max
 * Author(s): Kevin
 *
 * Helper function to find the maximum value in a BST
 */
template <class bstvalue, class bstobj>
bstobj BST<bstvalue, bstobj>::findMax(Nodeptr root)
{
    if (root->right == NULL)
    {
        return root->obj;
    }
    else
    {
        return findMin(root->left);

    }
}


/**Public functions*/

/**
 * BST Constructor
 * Author(s): Kevin
 *
 * Simply makes a root and makes size 0
 */
template <class bstvalue, class bstobj>
BST<bstvalue, bstobj>::BST()
{
    root = NULL;
    size = 0;
}

/**
 * BST Destructor
 * Author(s): Kevin
 *
 * Deletes the tree to free allocated memory
 */
template <class bstvalue, class bstobj>
BST<bstvalue, bstobj>::~BST()
{
    deleteTree(root);
}

/**
 * Is Empty
 * Author(s): Kevin
 *
 * Checks if the tree is empty.
 * Returns true if it is empty
 */
template <class bstvalue, class bstobj>
bool BST<bstvalue, bstobj>::isEmpty()
{
    return root == NULL;
}

/**
 * Get Size
 * Author(s): Kevin
 *
 * Returns the amount of objects stored in the BST
 */
template <class bstvalue, class bstobj>
int BST<bstvalue, bstobj>::getSize()
{
    return size;
}

/**
 * Add
 * Author(s): Kevin
 *
 * Wrapper function to addValue(). Adds an object to the tree.
 * Has the ability to add objects with the same bstvalue
 */
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

/**
 * Get Root
 * Author(s): Kevin
 *
 * Returns the object stored at the root.
 * Pre: List is not empty
 */
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

/**
 * Print In Order
 * Author(s): Kevin
 *
 * Wrapper function to printInOrder
 * Prints the BST in order
 */
template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::printInOrder()
{
    if (isEmpty()) cout << "Error: The tree is empty." << endl << endl;
    else inOrderPrint(root);
}

/**
 * Print Pre Order
 * Author(s): Kevin
 *
 * Wrapper function to printPreOrder
 * Prints the BST in pre order
 */
template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::printPreOrder()
{
    if (isEmpty()) cout << "Error: The tree is empty." << endl << endl;
    else preOrderPrint(root);
}

/**
 * Print Post Order
 * Author(s): Kevin
 *
 * Wrapper function to printPostOrder
 * Prints the BST in post order
 */
template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::printPostOrder()
{
    if (isEmpty()) cout << "Error: The tree is empty." << endl << endl;
    else postOrderPrint(root);
}

/**
 * Level Order Print
 * Author(s): Kevin
 *
 * Wrapper function to printLevelOrder
 * Shows the level of each object
 */
template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::levelOrderPrint()
{
    if (isEmpty()) cout << "Error: The tree is empty.\n";
    else printLevelOrder(root);
}

/**
 * Print In Order
 * Author(s): Kevin
 *
 * Wrapper function to inOrderPrint
 * Prints the BST in order
 * This function prints values that are within a certain range
 */
template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::printInOrder(bstvalue min, bstvalue max)
{
    if (isEmpty()) cout << "Error: The tree is empty." << endl << endl;
    else inOrderPrint(root, min, max);
}

/**
 * Print Pre Order
 * Author(s): Kevin
 *
 * Wrapper function to preOrderPrint
 * Prints the BST in pre order
 * This function prints values that are within a certain range
 */
template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::printPreOrder(bstvalue min, bstvalue max)
{
    if (isEmpty()) cout << "Error: The tree is empty." << endl << endl;
    else preOrderPrint(root, min, max);
}

/**
 * Print Post Order
 * Author(s): Kevin
 *
 * Wrapper function to postOrderPrint
 * Prints the BST in post order
 * This function prints values that are within a certain range
 */
template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::printPostOrder(bstvalue min, bstvalue max)
{
    if (isEmpty()) cout << "Error: The tree is empty." << endl << endl;
    else postOrderPrint(root, min, max);
}

/**
 * Get Vector In Order
 * Author(s): Kevin
 *
 * Wrapper function to vectorInOrder
 * Adds values to a vector in order
 */
template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::getVectorInOrder(vector<bstobj> &list)
{
    if (isEmpty()) cout << "Error: The tree is empty." << endl << endl;
    else inOrderVector(root, list);
}

/**
 * Get Vector In Order
 * Author(s): Kevin
 *
 * Wrapper function to vectorInOrder
 * Adds values to a vector in order
 * This function only adds values between a certain range
 */
template <class bstvalue, class bstobj>
void BST<bstvalue, bstobj>::getVectorInOrder(bstvalue min, bstvalue max, vector<bstobj> &list)
{
    if (isEmpty()) cout << "Error: The tree is empty." << endl << endl;
    else inOrderVector(root, min, max, list);
}

/**
 * Contains
 * Author(s): Kevin
 *
 * Wrapper function to containtsValue
 * Returns true if a value is found within the BST
 */
template <class bstvalue, class bstobj>
bool BST<bstvalue, bstobj>::contains(bstvalue value)
{
    if (isEmpty()) return false;
    if (value == root->data) return true;
    else return containsValue(root, value);
}

/**
 * Minimum
 * Author(s): Kevin
 *
 * Wrapper function to findMin
 * Returns the minimum object in the BST
 * Pre: BST is not empty
 */
template <class bstvalue, class bstobj>
bstobj BST<bstvalue, bstobj>::minimum()
{
    if (root == NULL)
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

/**
 * Maximum
 * Author(s): Kevin
 *
 * Wrapper function to findMax
 * Returns the maximum object in the BST
 * Pre: BST is not empty
 */
template <class bstvalue, class bstobj>
bstobj BST<bstvalue, bstobj>::maximum()
{
    if (root == NULL)
    {
        cout << "Minimum: Tree is empty" << endl;
        //will need to include cstdlib for exit below
        exit(-1); //you can also use assert here if desired
    }
    else
    {
        return findMax(root);
    }
}

#endif
