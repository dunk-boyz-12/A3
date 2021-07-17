//
//  AVL.hpp
//  Assignment_3
//
//  Created by Nicholas Buras on 6/28/21.
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

enum e_subTreeSide {
    RIGHT = 0,
    LEFT = 1
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
    void readFile(char*);
    //deletion
    void deleteNode(int);
    
    
private:
    s_Node* root;
    int nodeCount;
    bool quitProgram;
    
    void p_readFile(char*);
    s_Node* p_createNode(int);
    s_Node* p_rotateRight(s_Node*);
    s_Node* p_rotateLeft(s_Node*);
    void p_printTree(s_Node*);
    void p_formattedPrint(s_Node*,int);
    
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
    void p_deleteTree(s_Node*);
    void p_recDelete(s_Node* root);
    void p_deleteNode(s_Node*);
    void p_postDeletionHeightFix(s_Node*,int);
    void p_ManageDeletionCase(s_Node*,int);
    void p_handleDeletionCase(s_Node*,s_Node*,s_Node*,int);
    s_Node* p_findNode(s_Node*,int);
    s_Node* p_findPredecessor(s_Node*);
    s_Node* p_findSuccessor(s_Node*);
    s_Node* p_swapNodes(s_Node*,s_Node*);
};


#endif /* AVL_hpp */
