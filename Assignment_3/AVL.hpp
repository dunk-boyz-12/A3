//
//  AVL.hpp
//  Assignment_3
//
//  Created by Nicholas Buras on 7/3/21.
//

#ifndef AVL_hpp
#define AVL_hpp

#include <stdio.h>

struct s_Node {
    int value;
    int leftHeight;
    int rightHeight;
    s_Node* parent;
    s_Node* right;
    s_Node* left;
};

class c_AVL {
public:
    c_AVL();
    ~c_AVL();
    void insert(int);
    s_Node* createNode(int);
private:
    s_Node* root;
    int nodeCount;
    s_Node* p_createNode(int);
    s_Node* p_insert(s_Node*, s_Node*);
};


#endif /* AVL_hpp */
