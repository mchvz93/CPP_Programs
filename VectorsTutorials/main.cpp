//
//  main.cpp
//  VectorsTutorials
//
//  Created by Marco A. Chavez Jr. on 3/3/18.
//  Copyright © 2018 Marco A. Chavez Jr. All rights reserved.
//  format: vector<DataType> nameOfVector
//  myVector.push_back(value) -> adds an element to the END of the vector (also resizes it)
//  myVector.at(index) -> return element at specified index number
//  myVector.size() -> returns an unsigned int equal to the number of elements
//  myVector.begin() -> reads vector from first element (index 0)
//  myVector.insert(myVector.begin() + integer, new value) -> adds elements BEFORE specified index number
//  myVector.erase(myVector.begin() + integer) -> removes element AT specified index number
//  myVector.clear() -> removes all elements in vector
//  myVector.empty() -> returns boolean value if whether vector is emtpy
#include <iostream>
#include <vector>



void fillVector(std::vector<int>& newMyVector) {
    std::cout << "type in a list of numbers (-1 to stop): \n";
    int input;
    std::cin >> input;
    
    while (input != -1) {
        newMyVector.push_back(input);
        std::cin >> input;
        
    }
    std::cout << std::endl;
}

void printVector(const std::vector<int>& newMyVector) {
    
    std::cout << "Vector: " << std::endl;
    
    for (unsigned int i = 0; i < newMyVector.size(); i++) {
        std::cout << newMyVector[i] << " ";
    }
    
    std::cout << std::endl;
}

void reverse(const std::vector<int>& newMyVector) {
    std::cout << "Vector Reversed: " << std::endl;
    
    for (unsigned long i = newMyVector.size(); i > 0; i--){
        std::cout << newMyVector[i-1] << " ";
    }
    std::cout << std::endl;
}

void printEvens(const std::vector<int>& newMyVector) {
    
    std::cout << "Even elements in Vector: ";
    
    for (unsigned int i = 0; i < newMyVector.size(); i++) {
        if ((newMyVector[i] % 2) == 0) {        //if you want to print odds you write: if ((newMyVector[i] % 2) != 0)
            std::cout << newMyVector[i] << " ";
        }
    }
    std::cout << std::endl;
}

void replace(std::vector<int>& newMyVector) {
    int old;
    int replace;
    
    std::cout << "\nType in the first number to be replaced then type what number you want to replace: \n";
    std::cin >> old >> replace;
    
    for (unsigned int i = 0; i < newMyVector.size(); i++) {
        if (newMyVector[i] == old) {
            newMyVector[i] = replace;
        }
    }
    printVector(newMyVector);
    std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
// PROGRAM 1
//    std::vector<int> myVector;
//    myVector.push_back(3);
//    myVector.push_back(7);
//    myVector.push_back(4);
//    myVector.push_back(12);
//    myVector.push_back(9);
//
//    std::cout << "Vector: ";
//    for (unsigned int i = 0; i < myVector.size(); i++) {
//        std::cout << myVector[i] << " ";
//    }
//
//    myVector.insert(myVector.begin() + 3, 5);
//
//    std::cout << "Vector: ";
//    for (unsigned int i = 0; i < myVector.size(); i++) {
//        std::cout << myVector[i] << " ";
//    }
//
//    myVector.erase(myVector.begin() + 4);
//
//    std::cout << "Vector: ";
//    for (unsigned int i = 0; i < myVector.size(); i++) {
//        std::cout << myVector[i] << " ";
//    }
//
//
//    if (myVector.empty()) {
//        std::cout << "is empty!";
//    } else {
//        std::cout << "is not empty";
//    }
//
//    myVector.clear();
//
//    if (myVector.empty()) {
//        std::cout << "is empty!";
//    } else {
//        std::cout << "is not empty";
//    }
//
//
//    std::cout << std::endl;
//
//    return 0;
    
    std::vector<int> myVector;
    fillVector(myVector);
    printVector(myVector);
    reverse(myVector);
    printEvens(myVector);
    replace(myVector);
    
    return 0;
    
    /*
     OUTPUT:
     type in a list of numbers (-1 to stop):
     8
     10
     90
     30
     54
     23
     -1

     Vector:
     8 10 90 30 54 23
     Vector Reversed:
     23 54 30 90 10 8
     Even elements in Vector: 8 10 90 30 54

     Type in the first number to be replaced then type what number you want to replace:
     90
     100
     Vector:
     8 10 100 30 54 23

     Program ended with exit code: 0
     */

}
