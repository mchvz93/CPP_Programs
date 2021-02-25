//  functional code.
//  main.cpp
//  Dynamic Arrays: program demonstrates how to implement and use
//  dynamic arrays.
//  Referenced in C++ Data structures book pg. 173-175
//  Created by Marco A. Chavez Jr. on 1/15/18.
//  Copyright © 2018 Marco A. Chavez Jr. All rights reserved.
//

#include <iostream>
#include <cassert>
using namespace std;

void allocate_doubles(double*& p, size_t& n){
    cout << "How many doubles should I allocate? " << endl;
    cout << "Please type a positive integer answer: ";
    cin >> n;
    p = new double[n];  //this allocates the array of n doubles
    cout << "-------------------------------\n" << endl;
    
}
void fill_array(double data[], size_t n){
    size_t i;
    cout << "Please type " << n << " double numbers: " << endl;
    //reads the n numbers one at a time
    for (i = 0; i < n; ++i)
        cin >> data[i];
    cout << "-------------------------------\n" << endl;

}

void compare(const double data[], size_t n, double value){
    size_t i;
    for (i = 0; i < n; ++i){
        cout << data[i];
        if (data[i] < value)
            cout << " is less than ";
        else if (data[i] > value)
            cout <<" is more than ";
        else
            cout << " is equal to ";
        cout << value << endl;
    }
    
}

double average(const double data[], size_t n){
    size_t i;   //an array index
    double sum; //the sum of data[0] through data[n-1]
    assert(n > 0);
    // Add up the n numbers and return the average
    sum = 0;
    for (i = 0; i < n; ++i)
        sum += data[i];
    cout << "-------------------------------\n" << endl;
    return (sum/n);

}


int main() {
    double* numbers;  //this will point to the first component of the array only
    size_t array_size;
    double mean_value;
    //This will allocate an array of doubles to hold the users input.
    cout << "This program will compute the average of some numbers. The\n";
    cout << "numbers will be stored in an array of doubles that I will allocate.\n";
    allocate_doubles(numbers, array_size);
    
    //read the users input and compute the average
    fill_array(numbers, array_size);
    mean_value = average(numbers, array_size);
    
    //prints the output
    cout << "the average is: " << mean_value << endl;
    compare(numbers, array_size, mean_value);
    cout << "This was a mean program.\n";
    return EXIT_SUCCESS;
    
    
    //return 0;
}
