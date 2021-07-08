//
//  AVL.hpp
//  Assignment_3
//
//  Created by Nicholas Buras on 7/3/21.
//

#ifndef AVL_hpp
#define AVL_hpp

#include <stdio.h>

enum e_Commands {
    INSERT_NODE = 0,
    DELETE_NODE = 1,
    PRINT_TREE = 2,
    DELETE_TREE = 8,
    QUIT = 9
};

enum e_Cases {
    CASE_1 = 1,
    CASE_2 = 2,
    CASE_3 = 3,
    CASE_4 = 4
};

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
    s_Node* p_rotateRight(s_Node*);
    s_Node* p_rotateLeft(s_Node*);
    
    //INSERTION
    s_Node* p_insert(s_Node*, s_Node*);
    int p_manageInsertionCase(s_Node*,s_Node*,s_Node*);
    void p_updateFixHeight(s_Node*);
    void p_handleInsertCase(s_Node*,s_Node*,s_Node*,int);
    void p_caseOne(s_Node*,s_Node*,s_Node*);
    void p_caseTwo(s_Node*,s_Node*,s_Node*);
    void p_caseThree(s_Node*,s_Node*,s_Node*);
    void p_caseFour(s_Node*,s_Node*,s_Node*);
    
    //DELETION

    //fix tree
    //find situation (insert case) were in to fix, 1 of 4

    //all deletion functions
};


#endif /* AVL_hpp */
