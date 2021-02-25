//
//  main.cpp
//  Systutorials_multimap
//
//  Created by XxTheEyeOfSauronxX on 10/15/20.
//

#include <iostream>
#include <map>
struct FatKey { int x; int data[1000]; };

struct LightKey { int x; };

bool operator<(const FatKey& fk, const LightKey& lk) { return fk.x < lk.x; }
bool operator<(const LightKey& lk, const FatKey& fk) { return lk.x < fk.x; }
bool operator<(const FatKey& fk1, const FatKey& fk2) { return fk1.x < fk2.x; }

int main() {
    
// simple comparison demo
    std::multimap<int,char> example = {{1,'a'},{2,'b'}};


    auto search = example.find(2);
    if (search != example.end()) {
        std::cout << "Found " << search->first << " " << search->second << '\n';
    } else {
        std::cout << "Not found\n";
    }


// transparent comparison demo
    std::multimap<FatKey, char, std::less<>> example2 = { { {1, {} },'a'}, { {2, {} },'b'} };


    LightKey lk = {2};
    auto search2 = example2.find(lk);
    if (search2 != example2.end()) {
        std::cout << "Found " << search2->first.x << " " << search2->second << '\n';
    } else {
        std::cout << "Not found\n";
    }
}
