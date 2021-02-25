//
//  main.cpp
//  HashTablesYT
//
//  Created by XxTheEyeOfSauronxX on 9/13/20.
//  Copyright © 2020 Marco A. Chavez Jr. All rights reserved.
//

#include <iostream>
#include <list>
#include <cstring>


class HashTable {
private:
    static const int hashGroups = 10;
    std::list<std::pair<int, std::string>> table[hashGroups]; //list 1, index 0, list 2, index 1...
public:
    bool isEmpty() const;
    int hashFunction(int key);
    void insertItem(int key, std::string value);
    void removeItem(int key);
    std::string searchTable(int key);
    void printTable();
};

bool HashTable::isEmpty() const {
    int sum{};
    for (int i{}; i < hashGroups; i++) {
        sum += table[i].size();
    }

    if (!sum) {
        return true;
    }
    return false;
}

int HashTable::hashFunction(int key) {
    return key% hashGroups; //key: 905, in return this function will spit out 5
}

void HashTable::insertItem(int key, std::string value) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    bool keyExists = false;

    for (; bItr != end(cell); bItr++) {
        if (bItr->first == key) {
            keyExists = true;
            bItr->second = value;
            std::cout << "[WARNING] Key exists. Value replaced." << std::endl;
            break;
        }
    }

    if (!keyExists) {
        cell.emplace_back(key, value);
    }
    return;
}

void HashTable::removeItem(int key) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    bool keyExists = false;

    for (; bItr != end(cell); bItr++) {
        if (bItr->first == key) {
            keyExists = true;
            bItr = cell.erase(bItr);
            std::cout << "[INFO] item removed. " << std::endl;
            break;
        }
    }

    if (!keyExists) {
        std::cout << "[WARNING] key not found. pair not removed." << std::endl;
    }
    return;
}

void HashTable::printTable() {
    for (int i{}; i < hashGroups; i++) {
        if (table[i].size() == 0) continue;

        auto bItr = table[i].begin();
        for (; bItr != table[i].end(); bItr++) {
            std::cout << "[INFO] Key: " << bItr->first << "   Value: " << bItr->second << std::endl;
        }
    }
    return;
}


int main(int argc, const char * argv[]) {
    HashTable HT;

    if(HT.isEmpty()) {
        std::cout << "Correct answer. Good job." << std::endl;
    }
    else {
        std::cout << "oh oh. we need to check out code!" << std::endl;
    }

    HT.insertItem(905, "jim");
    HT.insertItem(201, "ash");
    HT.insertItem(332, "marco");
    HT.insertItem(124, "darcee");
    HT.insertItem(107, "rob");
    HT.insertItem(929, "bisbee");
    HT.insertItem(928, "emily");
    HT.insertItem(928, "sharon");

    HT.printTable();

    HT.removeItem(332);
    HT.removeItem(100);

    HT.printTable();

    std::cout << "checking to see if empty.. it shouldnt be. " << std::endl;


    if(HT.isEmpty()) {
        std::cout << "oh oh. we need to check out code!" << std::endl;
    }
    else {
        std::cout << "correct answer. good job!" << std::endl;
    }
    return 0;
}

/*
 OUTPUT:
 Correct answer. Good job.
 [WARNING] Key exists. Value replaced.
 [INFO] Key: 201   Value: ash
 [INFO] Key: 332   Value: marco
 [INFO] Key: 124   Value: darcee
 [INFO] Key: 905   Value: jim
 [INFO] Key: 107   Value: rob
 [INFO] Key: 928   Value: sharon
 [INFO] Key: 929   Value: bisbee
 [INFO] item removed.
 [WARNING] key not found. pair not removed.
 [INFO] Key: 201   Value: ash
 [INFO] Key: 124   Value: darcee
 [INFO] Key: 905   Value: jim
 [INFO] Key: 107   Value: rob
 [INFO] Key: 928   Value: sharon
 [INFO] Key: 929   Value: bisbee
 checking to see if empty.. it shouldnt be.
 correct answer. good job!
 */
