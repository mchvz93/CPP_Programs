//
//  main.cpp
//  WordTransformationMap
//
//  Created by XxTheEyeOfSauronxX on 8/25/20.
//  Copyright © 2020 Marco A. Chavez Jr. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>



std::map<std::string, std::string> buildMap(std::ifstream &map_file) {
    std::map<std::string, std::string> trans_map;
    std::string key;
    std::string value;
    
    while (map_file >> key && getline(map_file, value))
        if (value.size() > 1)
            trans_map[key] = value.substr(1);
        else
            throw std::runtime_error("no rule for " + key);
    
    return trans_map;
    
}

const std::string& transform(const std::string &s, const std::map<std::string, std::string> &m) {
    auto map_it = m.find(s);
    if (map_it != m.cend()) {
        return map_it->second;
    }
    else {
        return s;
    }
}

void word_transform(std::ifstream &map_file, std::ifstream &input) {
    auto trans_map = buildMap(map_file);
    std::string text;
    while(std::getline(input, text)){
        std::istringstream stream(text);
        std::string word;
        bool firstword = true;
        while (stream >> word) {
            if (firstword)
                firstword = false;
            else
                std::cout << " ";
            
            std::cout << transform(word, trans_map);
        }
        std::cout << std::endl;
    }
}


int main(int argc, const char * argv[]) {
    
    if (argc != 3){
        throw std::runtime_error("wrong number of arguments");
    }
    
    std::ifstream map_file(argv[1]);
    if (!map_file) {
        throw std::runtime_error("no transformation file");
    }
    
    std::ifstream input(argv[2]);
    if(!input) {
        throw std::runtime_error("no input file");
    }
    
    word_transform(map_file, input);
    
    return 0;
}
