//
//  main.cpp
//  Assignment_3
//
//  Created by Nicholas Buras on 6/28/21.
//

#include <iostream>
#include <fstream>
#include "customErrorClass.h"
#include "AVL.hpp"

int main(int argc, char* argv[]) {
    
    char* fileName = argv[1];
    
    try {
        c_AVL myTree;
        myTree.readFile(fileName);
    } catch(MyException& error) {
        std::cout << error.what();
        //continue;
    } catch(exception& error) {
        std::cout << error.what();
    }
}
