#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <iostream>
#include "Hash_node.h"


// Our own Hash_Map class
class Hash_Map {

    int capacity;
    // current size
    int size;
    // dummy node
    Hash_node* dummy;
    Hash_node** arr;

public:
    Hash_Map()
    {
        // Initial capacity of hash array
        capacity = 20;
        size = 0;
        arr = new Hash_node * [capacity];

        // Initialise all elements of array as NULL
        for (int i = 0; i < capacity; i++)
            arr[i] = NULL;

        // dummy node with value and key -1
        dummy =  new Hash_node('a' , "0");
    }
    // This implements hash function to find index
    // for a key
    int hashCode(char key)
    {
        return key % capacity;
    }

    // Function to add key value pair
    void insertNode(char key, string value)
    {
        Hash_node* temp = new Hash_node(key, value);

        // Apply hash function to find index for given key
        int hashIndex = hashCode(key);

        // find next free space
        while (arr[hashIndex] != NULL
            && arr[hashIndex]->key != key
            && arr[hashIndex]->key != -1) {
            hashIndex++;
            hashIndex %= capacity;
        }

        // if new node to be inserted
        // increase the current size
        if (arr[hashIndex] == NULL
            || arr[hashIndex]->key == -1)
            size++;
        arr[hashIndex] = temp;
    }

    // Function to delete a key value pair
    string deleteNode(int key)
    {
        // Apply hash function
        // to find index for given key
        int hashIndex = hashCode(key);

        // finding the node with given key
        while (arr[hashIndex] != NULL) {
            // if node found
            if (arr[hashIndex]->key == key) {
                Hash_node* temp = arr[hashIndex];

                // Insert dummy node here for further use
                arr[hashIndex] = dummy;

                // Reduce size
                size--;
                return temp->value;
            }
            hashIndex++;
            hashIndex %= capacity;
        }

        // If not found return null
        return "\0";
    }

    // Function to search the value for a given key
    string get(int key)
    {
        // Apply hash function to find index for given key
        int hashIndex = hashCode(key);
        int counter = 0;

        // finding the node with given key
        while (arr[hashIndex] != NULL) { // int counter =0; // BUG!

            if (counter++ > capacity) // to avoid infinite loop
                return NULL;

            // if node found return its value
            if (arr[hashIndex]->key == key)
                return arr[hashIndex]->value;
            hashIndex++;
            hashIndex %= capacity;
        }

        // If not found return null
        return NULL;
    }

    // Return current size
    int sizeofMap()
    {
        return size;
    }

    // Return true if size is 0
    bool isEmpty()
    {
        return size == 0;
    }

    // Function to display the stored key value pairs
 /*   void display()
    {
        for (int i = 0; i < capacity; i++) {
            if (arr[i] != NULL && arr[i]->key != -1)
                cout << "key = " << arr[i]->key
                << "  value = "
                << arr[i]->value << endl;
        }
    }
*/
};
#endif // HASH_MAP_H
