//
//  AVL.cpp
//  Assignment_3
//
//  Created by Nicholas Buras on 7/3/21.
//

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
