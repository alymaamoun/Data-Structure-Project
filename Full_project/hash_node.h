#ifndef HASH_NODE_H
#define HASH_NODE_H
#include <iostream>
#include<string>
// template to make class take any data type
using namespace std;

// Hash_node class
class Hash_node {
public:
    string value;
    char key;
    Hash_node(char key, string value) {
        this->key = key;
        this->value = value;
    }

};




#endif // HASH_NODE_H