//
//  AVL.cpp
//  Assignment_3
//
//  Created by Nicholas Buras on 7/3/21.
//
#include <iostream>

#include "AVL.hpp"
#include "customErrorClass.h"

/* ############################   PUBLIC FUNCTIONS   ############################ */
c_AVL::c_AVL() {
    this->root = nullptr;
    this->nodeCount = 0;
}

c_AVL::~c_AVL() {
    
}

s_Node* c_AVL::createNode(int value) {
    s_Node* newNode;
    if(value <= 0) {
        //throw exception
        throw MyException("shooooooooot ! ");
    } else {
        newNode = this->p_createNode(value);
    }
    return newNode;
}

void c_AVL::insert(int value) {
    s_Node* newNode = this->createNode(value);
    if(!newNode) {
        throw MyException("Error ! ");
    } else {
        //insert node into tree
        this->root = this->p_insert(this->root, newNode);
        //update node count
        this->nodeCount++;
        //fix node sub tree heights
        this->p_updateFixHeight(newNode);
    }
}
/* ############################   PRIVATE FUNCTIONS   ############################ */
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

/* #############   INSERTION FUNCTIONS   ############# */

s_Node* c_AVL::p_insert(s_Node* root, s_Node* node) {
    //throw exception if value is already in tree, add check for  that
    if(root == nullptr){
        return node;
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
            /* get insertion case, pass node of imbalance */
            insertionCase = this->p_manageInsertionCase(node, child, grandChild);
            this->p_handleInsertCase(node, child, grandChild, insertionCase);
            break;
        }
        /*track correct path - children/grandchildren nodes of node of imbalance
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
    
}

void c_AVL::p_caseTwo(s_Node* grandParent, s_Node* Parent, s_Node* child) {
    
}

void c_AVL::p_caseThree(s_Node* grandParent, s_Node* Parent, s_Node* child) {
    
}

void c_AVL::p_caseFour(s_Node* grandParent, s_Node* Parent, s_Node* child) {
    
}

/* #############   DELETEION FUNCTIONS   ############# */
