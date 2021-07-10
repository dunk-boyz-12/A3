//
//  AVL.cpp
//  Assignment_3
//
//  Created by Nicholas Buras on 6/28/21.
//
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sys/stat.h>

#include "AVL.hpp"
#include "customErrorClass.h"

/* ############################   PUBLIC FUNCTIONS   ############################ */
c_AVL::c_AVL() {
    this->root = nullptr;
    this->nodeCount = 0;
}

c_AVL::~c_AVL() {
    //if 9(Quit) is not encountered
    //if(!this->quitProgram){
      //  this->p_deleteTree(this->root);
    //}
}

s_Node* c_AVL::createNode(int value) {
    s_Node* newNode;
    if(value < 0) {
        //throw exception
        throw MyException("Error ! Node values must be a positive integer or 0.");
    } else {
        newNode = this->p_createNode(value);
    }
    return newNode;
}

void c_AVL::insert(int value) {
    s_Node* newNode = this->createNode(value);
    if(!newNode) {
        throw MyException("Error ! Node with a value: was not created.");
    } else {
        std::cout << "Inserting Node with value: " << newNode->value << std::endl;
        //insert node into tree
        this->root = this->p_insert(this->root, newNode);
        //update node count
        //this->nodeCount++;
        //fix node sub tree heights
        this->p_updateFixHeight(newNode);
    }
}

void c_AVL::readFile(char* fileName) {
    //check that file is not empty
    //struct stat fileStat;
    //this->fileSize = fileStat.st_size;
    //if(this->fileSize == 0){
        //throw MyException("Error ! Could not open desired input file.");
    //} else {
        this->p_readFile(fileName);
    //}
}
/* ############################   PRIVATE FUNCTIONS   ############################ */
void c_AVL::p_readFile(char* fileName) {
    this->quitProgram = false;
    ifstream fileToRead(fileName); //open input file
    int inputData;
    
    if(!fileToRead.is_open()){
        throw MyException("Error ! Could not open the input file correctly.");
    } else {
        while (!fileToRead.eof() && !quitProgram) {
            fileToRead >> inputData;
            switch (inputData) {
                case INSERT_NODE:
                    fileToRead >> inputData;
                    std::cout << "Inserting Node with value: " << inputData << std::endl;
                    this->insert(inputData);
                    break;
                case DELETE_NODE:
                    fileToRead >> inputData;
                    //call to delete node functions
                    std::cout << "Deleting Node with value: " << inputData << std::endl;
                    break;
                case PRINT_TREE:
                    std::cout << "Current AVL Tree" << std::endl;
                    this->p_printTree(this->root);
                    break;
                case DELETE_TREE:
                    std::cout << "Deleting AVL Tree" << std::endl;
                    this->p_deleteTree(this->root);
                    break;
                case QUIT:
                    //set quit flag
                    this->quitProgram = true;
                    std::cout << "Quiting Program, GoodBye !";
                    break;
            }
        }
    }
    //close file
    fileToRead.close();
}

s_Node* c_AVL::p_createNode(int value) {
    s_Node* newNode = new s_Node();
    newNode->value = value;
    newNode->parent = nullptr;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->leftHeight = 0;
    newNode->rightHeight = 0;
    return newNode;
}

s_Node* c_AVL::p_rotateRight(s_Node* nodeToRotate) {
    s_Node* leftChild = nodeToRotate->left;
    s_Node* Parent = nodeToRotate->parent;
    //update right & left ptrs
    nodeToRotate->left = leftChild->right;
    leftChild->right = nodeToRotate;
    //update parent ptrs
    nodeToRotate->parent = leftChild;
    leftChild->parent = Parent;
    s_Node* newLeftChild = nodeToRotate->left;
    if(newLeftChild) { // <-- incase new child the rotated node gains is null
        newLeftChild->parent = nodeToRotate;
    }
    if(leftChild->parent == nullptr){ //if root
        this->root = leftChild;
    } else { //find if node to rotate is a left/right subtree and update parents ptr to new parent node after rotation
        if(nodeToRotate == Parent->left) {
            Parent->left = leftChild;
        } else {
            Parent->right = leftChild;
        }
    }
    //update rotated node left height (newly gained child)
    if(nodeToRotate->left){
        nodeToRotate->leftHeight = max(nodeToRotate->left->leftHeight, nodeToRotate->left->rightHeight) + 1;
    } else {
        nodeToRotate->leftHeight = 0;
    }
    //update new parent node right height
    leftChild->rightHeight = max(leftChild->right->leftHeight, leftChild->right->rightHeight) + 1;
    //return node that becomes parent of node of imbalance
    return leftChild;
}

s_Node* c_AVL::p_rotateLeft(s_Node* nodeToRotate) {
    s_Node* rightChild = nodeToRotate->right;
    s_Node* Parent = nodeToRotate->parent;
    //update right & left ptrs
    nodeToRotate->right = rightChild->left;
    rightChild->left = nodeToRotate;
    //update parent ptrs
    nodeToRotate->parent = rightChild;
    rightChild->parent = Parent;
    s_Node* newRightChild = nodeToRotate->right;
    if(newRightChild) { // <-- incase new child the rotated node gains is null
        newRightChild->parent = nodeToRotate;
    }
    if(rightChild->parent == nullptr){ //if root
        this->root = rightChild;
    } else { //find if node to rotate is a left/right subtree and update parents ptr to new parent node after rotation
        if(nodeToRotate == Parent->left) {
            Parent->left = rightChild;
        } else {
            Parent->right = rightChild;
        }
    }
    //update rotated node right height (newly gained child)
    if(nodeToRotate->right){
        nodeToRotate->rightHeight = max(nodeToRotate->right->leftHeight, nodeToRotate->right->rightHeight) + 1;
    } else {
        nodeToRotate->rightHeight = 0;
    }
    //update new parent node left height
    rightChild->leftHeight = max(rightChild->left->leftHeight, rightChild->left->rightHeight) + 1;
    //return node that becomes parent of node of imbalance
    return rightChild;
}

void c_AVL::p_printTree(s_Node* root) {
    int indent = 4;
    if(root == nullptr) {
        std::cout << "Cannot print tree, it is empty.";
        //throw MyException("Error ! Tree is empty.");;
    } else {
        this->p_formattedPrint(root, indent);
    }
}

void c_AVL::p_formattedPrint(s_Node* root, int indent){
    if(root == nullptr) {
        return;
    } else {
        this->p_formattedPrint(root->left, indent + 4);
        if(indent){
            std::cout << setw(indent);
        }
        std::cout << root->value << std::endl;
        this->p_formattedPrint(root->right, indent + 4);
    }
}

/* #############   INSERTION FUNCTIONS   ############# */

s_Node* c_AVL::p_insert(s_Node* root, s_Node* node) {
    //throw exception if value is already in tree, add check for  that
    if(root == nullptr){
        this->nodeCount++;
        return node;
    } else if(root->value == node->value){
        std::cout << "Node with value: " << node->value << " already exists in the tree. Skipping to next integer." << endl;
        return root;
    } else if(node->value < root->value) {
        root->left = this->p_insert(root->left, node);
        //keep track of parent
        root->left->parent = root;
    } else {
        root->right = this->p_insert(root->right, node);
        //keep track of parent
        root->right->parent = root;
    }
    return root;
}

void c_AVL::p_updateFixHeight(s_Node* node) {
    int rightSubTreeMax;
    int leftSubTreeMax;
    int insertionCase;
    //to track path for the manage case function
    s_Node* child = node;
    s_Node* grandChild = node;
    while(node != nullptr) {
        //get left sub tree max sub tree height
        if(node->left != nullptr){
            leftSubTreeMax = max(node->left->leftHeight,node->left->rightHeight);
            node->leftHeight = leftSubTreeMax + 1;
        }
        //get right sub tree max sub tree height
        if(node->right != nullptr) {
            rightSubTreeMax = max(node->right->leftHeight,node->right->rightHeight);
            node->rightHeight = rightSubTreeMax + 1;
        }
        //check for height imbalance
        if(abs(node->leftHeight - node->rightHeight) > 1) {
            /* get insertion case, pass node of imbalance and "path back" */
            insertionCase = this->p_manageInsertionCase(node, child, grandChild);
            this->p_handleInsertCase(node, child, grandChild, insertionCase);
            //exit loop, tree is fixed
            break;
        }
        /* track correct path - children/grandchildren nodes of node of imbalance
        for case management */
        if(child->left || child->right) {
            grandChild = grandChild->parent;
        }
        if(node->left || node->right) {
            child = child->parent;
        }
        //continue checking up the tree
        node = node->parent;
    };
}

int c_AVL::p_manageInsertionCase(s_Node* nodeOfImbalance, s_Node* child, s_Node* grandChild) {
    e_Cases caseNumber;
    //find formation of children(case) based on the path
    if(child == nodeOfImbalance->left){
        if(grandChild == child->right){
            caseNumber = CASE_1;
        } else {
            caseNumber = CASE_3;
        }
    } else {
        if(grandChild == child->right){
            caseNumber = CASE_4;
        } else {
            caseNumber = CASE_2;
        }
    }
    return caseNumber;
}

void c_AVL::p_handleInsertCase(s_Node* nodeOfImbalance, s_Node* child, s_Node* grandChild, int caseNumber) {
    switch (caseNumber) {
        case CASE_1:
            this->p_caseOne(nodeOfImbalance, child, grandChild);
            break;
        case CASE_2:
            this->p_caseTwo(nodeOfImbalance, child, grandChild);
            break;
        case CASE_3:
            this->p_caseThree(nodeOfImbalance, child, grandChild);
            break;
        case CASE_4:
            this->p_caseFour(nodeOfImbalance, child, grandChild);
            break;
    }
}

void c_AVL::p_caseOne(s_Node* grandParent, s_Node* Parent, s_Node* child) {
    //gp is node of imbalance
    //left rotate parent
    s_Node* nodeToRotate = Parent;
    nodeToRotate = this->p_rotateLeft(nodeToRotate);
    //right rotate gp
    nodeToRotate = grandParent;
    nodeToRotate = this->p_rotateRight(nodeToRotate);
}

void c_AVL::p_caseTwo(s_Node* grandParent, s_Node* Parent, s_Node* child) {
    //gp is node of imbalance
    //right rotate parent
    s_Node* nodeToRotate = Parent;
    nodeToRotate = this->p_rotateRight(nodeToRotate);
    //left rotate gp
    nodeToRotate = grandParent;
    nodeToRotate = this->p_rotateLeft(nodeToRotate);
}

void c_AVL::p_caseThree(s_Node* grandParent, s_Node* Parent, s_Node* child) {
    //right rotate gp
    s_Node* nodeToRotate = grandParent;
    grandParent = this->p_rotateRight(nodeToRotate);
}

void c_AVL::p_caseFour(s_Node* grandParent, s_Node* Parent, s_Node* child) {
    //left rotate gp
    s_Node* nodeToRotate = grandParent;
    grandParent = this->p_rotateLeft(nodeToRotate);
}

/* #############   DELETEION FUNCTIONS   ############# */

void c_AVL::p_deleteTree(s_Node* root) {
    if(root == NULL) {
        std::cout << "Cannot delete tree, it is empty." << std::endl;
    } else {
        this->p_recDelete(root);
    }
    //reset root
    this->root = nullptr;
}

void c_AVL::p_recDelete(s_Node* root) {
    if(root == NULL) {
        return;
    } else {
        this->p_recDelete(root->left);
        this->p_recDelete(root->right);
        delete root;
    }
}
