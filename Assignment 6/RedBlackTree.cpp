//************************************************************************
// ASU CSE310 Assignment #6 Spring 2024
// Author: Ethan Roldan
// ASU ID: 1223945385
// Description: Red black tree implementation. See RedBlackTree.h
//              for the Red Black Tree definition
//************************************************************************

//include the relevant header file
//----
#include "RedBlackTree.h"

using namespace std;

//*******************************************************************
//constructor
RedBlackTree::RedBlackTree()
{
    // initialize the RBT as an empty root
    root = nullptr;
}

//*******************************************************************
//destructor
RedBlackTree::~RedBlackTree()
{
    // call the deleteNode function on the root and return/print the amount of nodes deleted
    int nodeSize = deleteNode(root);
    cout << "The number of nodes deleted: " << nodeSize << endl;
}

//**************************************************************
//Accessor for the root of the red-black tree
Node* RedBlackTree::getRoot() {
    return root;
}

//*******************************************************************
//delete the sub-tree rooted at 'node' and return number of nodes deleted
//This should be defined as a recursive function
int RedBlackTree::deleteNode(Node *node) {
    // we have a leaf node, stop recursive calls and delete current node
    if(node == nullptr) {
        delete node;
        return 0;
    }

    // if the current node has a left or right child, then recursively call delete function on children
    int left = deleteNode(node->leftChild);
    int right = deleteNode(node->rightChild);

    return left + right + 1;
}

//****************************************************************
//This is the general BST insertion operation.
//It does not care about the color of the newly added node.
void RedBlackTree::treeInsert(int vin, string model, string make, double price) {
    // Initialize a new node with the given properties
    Node* newCar = new Node();
    newCar->vin = vin;
    newCar->model = model;
    newCar->make = make;
    newCar->price = price;
    newCar->color = "RED";
    newCar->parent = nullptr;
    newCar->leftChild = nullptr;
    newCar->rightChild = nullptr;

    // if the tree is empty, change color to black and insert into root
    if(root == nullptr) {
        newCar->color = "BLACK";
        root = newCar;
        return;
    }
    // Traverse down until we find a leaf node, if vin is a duplicate then delete the new car and stop insertion
    Node* p = nullptr;
    Node* c = root;
    while(c != nullptr) {
        p = c;
        if (vin < c->vin) {
            c = c->leftChild;
        } else if (vin > c->vin) {
            c = c->rightChild;
        } else {
            delete newCar;
            return;
        }
    }
    // make the parent of the new car the found leaf node
    newCar->parent = p;
    // if the parent is null, we insert into the root
    if(p == nullptr) {
        newCar->color = "BLACK";
        root = newCar;
    } else {
        // we have a new leaf node, insert into left or right depending on greater or less than parent node
        if (vin < p->vin) {
            p->leftChild = newCar;
        } else {
            p->rightChild = newCar;
        }
    }

    // if the parent of the new node is red, we have a violation and we need to fixup
    if(p->color.compare("RED") == 0) {
        fixUp(newCar);
    }
}


//*******************************************************************
//At beginning, each newly added node will always be RED,
//this may violate the red-black tree property #4. fixUp()
//function will restore the property.
void RedBlackTree::fixUp(Node *node) {
    while (node != root && node->parent->color == "RED") {
        if (node->parent == node->parent->parent->leftChild) {
            Node* uncle = node->parent->parent->rightChild;
            if (uncle != nullptr && uncle->color == "RED") {
                node->parent->color = "BLACK";
                uncle->color = "BLACK";
                node->parent->parent->color = "RED";
                node = node->parent->parent;
            } else {
                if (node == node->parent->rightChild) {
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->color = "BLACK";
                node->parent->parent->color = "RED";
                rightRotate(node->parent->parent);
            }
        } else {
            Node* uncle = node->parent->parent->leftChild;
            if (uncle != nullptr && uncle->color == "RED") {
                node->parent->color = "BLACK";
                uncle->color = "BLACK";
                node->parent->parent->color = "RED";
                node = node->parent->parent;
            } else {
                if (node == node->parent->leftChild) {
                    node = node->parent;
                    rightRotate(node);
                }
                node->parent->color = "BLACK";
                node->parent->parent->color = "RED";
                leftRotate(node->parent->parent);
            }
        }
    }
    root->color = "BLACK";
}

//*****************************************************
//This function print the pre-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::preOrderTraversal(Node *node) {
    print(node);
    if(node->leftChild != nullptr) preOrderTraversal(node->leftChild);
    if(node->rightChild != nullptr) preOrderTraversal(node->rightChild);
}

//**************************************************
//This function print the in-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::inorderTraversal(Node *node) {
    if(node != nullptr) {
        inorderTraversal(node->leftChild);
        print(node);
        inorderTraversal(node->rightChild);
    }
}

//**************************************************
//This function print the post-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::postOrderTraversal(Node *node) {
    if(node->leftChild != nullptr) postOrderTraversal(node->leftChild);
    if(node->rightChild != nullptr) postOrderTraversal(node->rightChild);
    print(node);
}

//**************************************************************
//This function returns a pointer points to the minimum node from
//the current sub-tree rooted at 'node'. It should be designed as
//a recursive function
Node* RedBlackTree::findMinimumNode(Node *node) {
    while(node->leftChild != nullptr) {
        node = node->leftChild;
    }
    return node;
}

//**************************************************************
//This function returns a pointer points to the maximum node from
//the current sub-tree rooted at 'node'. It should be designed as
//a recursive function
Node* RedBlackTree::findMaximumNode(Node *node) {
    while(node->rightChild != nullptr) {
        node = node->rightChild;
    }
    return node;
}

//**************************************************************
//This function search the tree for a given key of a Car
//Note: key is the combination of vin, model and make of the Car
//It returns a pointer points to the node if founded; otherwise it returns NULL
Node* RedBlackTree::treeSearch(int vin, std::string model, std::string make) {
    Node* temp = root;
    while(temp != nullptr) {
        if(vin < temp->vin) {
            temp = temp->leftChild;
        } else if(vin > temp->vin) {
            temp = temp->rightChild;
        } else {
            if(!(model == temp->model && make == temp->make)) {
                temp = nullptr;
            }
            break;
        }
    }
    cout << left;
    cout << setw(8)  << vin
         << setw(12) << model
         << setw(13) << make
         << "is" << ((temp != nullptr) ? "" : " NOT") << " FOUND.\n";
    return temp;
}

//****************************************************
//This function left-rotate the BST rooted at 'node'
void RedBlackTree::leftRotate(Node *node) {
    Node* y = node->rightChild;
    node->rightChild = y->leftChild;
    if (y->leftChild != nullptr)
        y->leftChild->parent = node;
    y->parent = node->parent;
    if (node->parent == nullptr)
        root = y;
    else if (node == node->parent->leftChild)
        node->parent->leftChild = y;
    else
        node->parent->rightChild = y;
    y->leftChild = node;
    node->parent = y;
}

//***************************************************
//This function right-rotate the BST rooted at 'node'
void RedBlackTree::rightRotate(Node *node) {
    Node* x = node->leftChild;
    node->leftChild = x->rightChild;
    if (x->rightChild != nullptr)
        x->rightChild->parent = node;
    x->parent = node->parent;
    if (node->parent == nullptr)
        root = x;
    else if (node == node->parent->rightChild)
        node->parent->rightChild = x;
    else
        node->parent->leftChild = x;
    x->rightChild = node;
    node->parent = x;
}

//**************************************************************
//This function finds the predecessor of the given 'node'
//it prints the relevant predecessor info. on screen and also
//return a pointer that points to the predecessor
Node* RedBlackTree::findPredecessorNode(Node *node) {
    if(node->leftChild != nullptr) {
        return findMinimumNode(node->leftChild);
    } else {
        Node* parent = node->parent;
        while(parent != nullptr && node == parent->leftChild) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }
}

//**************************************************************
//This function finds the successor of the given 'node'
//it prints the relevant successor info. on screen and also return
//a pointer that points to the successor node
Node* RedBlackTree::findSuccessorNode(Node *node) {
    if(node->rightChild != nullptr) {
        return findMinimumNode(node->rightChild);
    } else {
        Node* parent = node->parent;
        while(parent != nullptr && node == parent->rightChild) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }
}

//****************************************************************
//This function find the minimum node of the entire red-black tree
//It print out the minimum node info. on screen if tree is not empty
//or print Tree is empty. No Minimum. message on screen.
void RedBlackTree::treeMinimum() {
    cout << "The MINIMUM is:\n";
    print(findMinimumNode(root));
}

//**************************************************************
//This function find the maximum node of the entire red-black tree
//It print out the maximum node info. on screen if tree is not empty
//or print Tree is empty. No Maximum. message on screen.
void RedBlackTree::treeMaximum() {
    cout << "The MAXIMUM is:\n";
    print(findMaximumNode(root));
}

//****************************************************************************
//This function print out the pre-order traversal of the entire red-black tree
void RedBlackTree::treePreorder() {
    preOrderTraversal(root);
}

//***************************************************************************
//This function print out the in-order traversal of the entire red-black tree
void RedBlackTree::treeInorder() {
    inorderTraversal(root);
}

//*****************************************************************************
//This function print out the post-order traversal of the entire red-black tree
void RedBlackTree::treePostorder() {
    postOrderTraversal(root);
}

//******************************************************************
//Given a Car key, this function first check whether the
//Car is inside the tree or not, if it is inside, it will print
//its predecessor info. on screen, if not, it print an error message
void RedBlackTree::treePredecessor(int vin, std::string model, std::string make) {
    Node* temp = treeSearch(vin, model, make);
    if(temp != nullptr) {
        if(findPredecessorNode(temp) != nullptr) {
            cout << "Its Predecessor is: \n";
            print(findPredecessorNode(temp));
        } else {
            cout << "Its Predecessor does NOT EXIST\n";
        }
    }
}

//******************************************************************
//Given a Car key, this function first check whether the
//Car is inside the tree or not, if it is inside, it will print
//its successor info. on screen, if not, it print an error message
void RedBlackTree::treeSucessor(int vin, std::string model, std::string make) {
    Node* temp = treeSearch(vin, model, make);
    if(temp != nullptr) {
        if(findSuccessorNode(temp) != nullptr) {
            cout << "Its Successor is: \n";
            print(findSuccessorNode(temp));
        } else {
            cout << "Its Successor does NOT EXIST\n";
        }
    }
}

//**************************************************************
//This function create a node from the given info., then insert
//the node inside the red-black tree. Note: at beginning, the newly
//added node should always be 'RED'

//write your own code according to red-black tree definition
//----

//******************************************************************
//Given a 'node', this function prints all the node information on screen
void RedBlackTree::print(Node *node)
{
    cout << left;
    cout << setw(8)  << node->vin
         << setw(12) << node->model
         << setw(12) << node->make
         << setw(10) << fixed << setprecision(2) << node->price;
    cout << right << setw(7) << node->color << endl;
}

//**************************************************************
//Given a Node 'node1', this function compares it with another
//node's key.
//key is a string combination of vin + model + make
//It returns a negative number if in alphabetical order, key2 is
//in front of 'node1'; otherwise it returns a positive number

//write your own code according to red-black tree definition
//----