/*
* File: BST.cpp
* Author: Jossie Batisso
* Description: This file deals with the manipulation of a binary tree and implamenetation of the
* code for adding, retrieving information, and the deletion of node.
*/
#include "BST.h"
#include <iostream>
#include <cstdlib>

using namespace std;

//constructor
BST::BST(){
    root = nullptr;
}

/*deconstructor
Description: Dynamically Deallocates node pointers when gone out of scope of program
Pre-Condition: Tree exists
Post-condtion: Tree's gone
*/
BST::~BST(){
    RemoveSubTree(root);
    root = nullptr;
}

/*
Description: Removing the nodes in the subtree given a node
Pre-condition: Tree exists, and a valid node is passed as a parameter
Post-conditino: All the nodes in the subtree are removed
*/
void BST::RemoveSubTree(node* ptr){
    if(ptr != nullptr){
        if(ptr->left != nullptr){
            RemoveSubTree(ptr->left);
        }
        if(ptr->right != nullptr){
            RemoveSubTree(ptr->right);
        }
        cout << ptr->key << " being deleted." << endl;
        delete ptr;
    }
}

// creating a new leaf
/*
Description: Creating a new leaf
Pre-Condition: Key value exist
Post-condition: Node containing a key is created
*/
BST::node* BST::CreateLeaf(int key){
    // initializing the data in the new leaf node
    node* n = new node;
    n->key = key;
    n->left = nullptr;
    n->right = nullptr;
    return n;
}

// Public function for adding leaf
void BST::Addleaf(int key){
    AddLeafPrivate(key, root);
}


/*
Description: Adding a node in the correct spot on the tree
Pre-Condition: a valid node exist
Post-condition: Node is placed in correct spot in the tree
*/
void BST::AddLeafPrivate(int key, node *ptr){
    if(root == nullptr){
        root = CreateLeaf(key);
    }
    // if the key value is less than the node key
    else if (key < ptr->key){
        // if the left isn't empty
        if(ptr->left != nullptr){
            // recursively checks the left most
            AddLeafPrivate(key, ptr->left);
        }else{
            ptr->left = CreateLeaf(key);
        }
    }
    // if the key is greater than the current key value 
    else if (key > ptr->key){
        // if the right isn't empty
        if(ptr->right != nullptr){
            // recursively checks the right child to find it's position
            AddLeafPrivate(key, ptr->right);
        }else{
            ptr->right = CreateLeaf(key);
        }
    }
    else{
        cout << "Key " << key << " has already been added to the tree." << endl;
    }
}

// Public Function for PrintInOrder
void BST::PrintInOrder(){
    PrintInOrderPrivate(root);
}


/*
Description: prints the key values in order from least to greatest
Pre-Condition:  Tree exist
Post-Condition: Key values are printed from least to greatest (left to right)
*/
void BST::PrintInOrderPrivate(node *ptr){
    if(root != nullptr){
        if(ptr->left != nullptr){
            PrintInOrderPrivate(ptr->left);
        }
        cout << ptr->key << " ";
        if(ptr->right != nullptr){
             PrintInOrderPrivate(ptr->right);
        }
    }
    else{
        cout << "Tree is empty" << endl;
    }
}

// Public function for ReturnNode
BST::node *BST::ReturnNode(int key){
    return ReturnNodePrivate(key, root);
}

/*
Description: Returns node given a key value. Used for checking if a key exists in the tree.
Pre-Condition: Key is passed from user.
Post-Condition: Node ptr is return corresponding to the key
*/
BST::node *BST::ReturnNodePrivate(int key, node* ptr){
    if(ptr != nullptr){
        // checking if the key is found
        if(ptr->key == key){
            return ptr;
        }
        else{
            // if the key is less than the current key, go left
            if(key < ptr->key){
                return ReturnNodePrivate(key, ptr->left);
            }
            else{
                // else check the right side of the tree
                return ReturnNodePrivate(key, ptr->right);
            }
        }
    }
    else{
        return nullptr;
    }
}

/*
* Description: returning the root key
* Pre-Condition: tree exist
* Post-Condition: Returning the root key value
*/
int BST::ReturnRootKey(){
    if( root != nullptr){
        return root->key;
    }
    else{
        return -1000;
    }
}

/*
* Description: Prints out the children of a given node
* Pre-Condition: Node with key exist
* Post-Condition: Children key values are outputed
*/
void BST::PrintChildren(int key){
    node *ptr = ReturnNode(key);

    if(ptr != nullptr){
        cout << "Parent Node = " << ptr->key << endl;
        ptr->left == nullptr ? cout << "Left child = NULL" << endl : cout << "Left Child = "<< ptr->left->key << endl;
        ptr->right == nullptr ? cout << "Right child = NULL" << endl : cout << "Right Child = "<< ptr->right->key << endl;
    }
    else{
        cout << "Key" << key << " is not in the tree" << endl;
    }
}

// Public for FindSmallestPrivate
int BST::FindSmallest(){
    return FindSmallestPrivate(root);
}

/*
* Description: 
* Post-Condition: 
*  Pre-Condition: 
*/
int BST::FindSmallestPrivate(node *ptr){
    // checking whether the tree is empty or not
    if(root == nullptr){
        cout << "This tree is empty" << endl;
        return -1000;
    }
    // checking if the left side is empty
    else{
        // if not, move on to smaller value on the left
        if(ptr->left != nullptr){
            return FindSmallestPrivate(ptr->left);
        }
        // else return the key itself as it's the smallest value.
        else{
            return ptr->key;
        }
    }
}

// Public for RemoveNodePrivate
void BST::RemoveNode(int key){
    RemoveNodePrivate(key, root);
}

/*
* Description: 
* Post-Condition: 
* Pre-Condition: 
*/
void BST::RemoveNodePrivate(int key, node* parent){
    // tree not empty
    if(root != nullptr){
        // removing the root
        if(root->key == key){
            RemoveRootMatch();
        }
        else{
            // checking if the key is less than the parent and left child isn't empty
            if(key < parent->key && parent->left != nullptr){
                // turinary operator for if the child's key matches, or doesn't match
                parent->left->key == key ? RemoveMatch(parent, parent->left, true): 
                RemoveNodePrivate(key, parent->left);
            }
            // checks the right child
            else if(key > parent->key && parent->right != nullptr){
                // turinary operator for if the child's key matches, or doesn't match
                parent->right->key == key ? RemoveMatch(parent, parent->right, false): 
                RemoveNodePrivate(key, parent->right);
            }
            else{
                cout << "The key: " << key << " was not found in the tree" << endl;
            }
        }
    }
    else{
        cout << "Tree is empty" << endl;
    }
}

/*
* Description: 
* Post-Condition: 
* Pre-Condition: 
*/
void BST::RemoveRootMatch(){
    if(root != nullptr){
        node* delptr = root;
        int rootKey = root->key;
        int smallestInRight;

        // case 0 - 0 children
        if(root->left == nullptr && root->right == nullptr){
            root = nullptr;
            delete delptr;
        }
        // case 1 - 1 child
        else if(root->left == nullptr && root->right != nullptr){
            root = root->right;
            delptr->right = nullptr;
            delete delptr;
            cout << "Root node with key: " << rootKey << " was deleted. " <<
            "The new root contains key: " << root->key << endl;
        }
        else if(root->right == nullptr && root->left != nullptr){
            root = root->left;
            delptr->left = nullptr;
            // delete delptr;
            cout << "Root knode with key: " << rootKey << " was deleted. " <<
            "The new root contains key: " << root->key << endl;
        }
        // case 2 - 2 children
        else{
            smallestInRight = FindSmallestPrivate(root->right);
            RemoveNodePrivate(smallestInRight, root);
            root->key = smallestInRight;
            cout << "The root key containing key: " << rootKey <<
            " was overwritten with key: " << root->key << endl;
        }
    }
    else{
        cout << "cannot remove root. The tree is empty" << endl;
    } 
}

void BST::RemoveMatch(node* parent, node* match, bool left){
    if(root != nullptr){
        node* delPtr;
        int matchKey = match->key;
        int smallest;
        // case 0 - 0 children
        if(match->left == nullptr && match->right == nullptr){
            delPtr = match;
            left == true ? parent->left = nullptr : parent->right = nullptr;
            delete delPtr;
            cout << "The node containing key: " << matchKey << " was removed" << endl;
        }
        
        // case 1 -1 child
        else if(match->left == nullptr && match->right != nullptr){
            // if the match is the parent's left child, connect the parent's left with right child
            // vise versa
            left == true ? parent->left = match->right : parent->right = match->right;
            // disconnecting the match
            match->right = nullptr;
            delPtr = match;
            delete delPtr;
            cout << "The node containing key: " << matchKey << " was removed" << endl;

        }
        else if(match->right == nullptr && match->left != nullptr){
            // if the match is the parent's left child, connect the parent's left with right child
            // vise versa
            left == true ? parent->left = match->left : parent->right = match->left;
            // disconnecting the match
            match->left = nullptr;
            delPtr = match;
            delete delPtr;
            cout << "The node containing key: " << matchKey << " was removed" << endl;

        }

        //case 2 - 2 children
        else{
            // finding the smallest value on the right to connect the graph
            smallest = FindSmallestPrivate(match->right);
            // removing the smallest on right (basically moving it up to the removed key spot)
            RemoveNodePrivate(smallest,match);
            // connecting the graph, not deleting the match node
            match->key = smallest;
        }
    }
    else{
        cout << "Cannot remove match. Tree is empty" << endl;
    }
}