#ifndef HASHMAP_H
#define HASHMAP_H

#include "linkedlist.h"
#include "llnode.h"
#include <functional>
#include <vector>
#include <string>

template <class K, class V>
class HashMap {
private:
    struct HashMapEntry {
        K key;
        V value;
        HashMapEntry(const K& k, const V& v) : key(k), value(v) {}
    };

    typedef linkedlist::LinkedList<K, V> LinkedListType;

    LinkedListType** array;
    size_t size;
    void resize(size_t new_size);
    HashMapEntry* getEntry(const K& key);

public:
    //ALL OF THE FUNCTIONS BELOW ARE BASED OFF HW4 SOLUTIONS / CSE017 HASHMAP IMPLEMENTATION

 
size_t hash(const K& key) const{
    std::hash<K> hashTool;
    return hashTool(key) % size;
}

//  
// void HashMap<K, V>::resize(size_t new_size){
//     LinkedList<HashMapEntry<K, V>>** old = array;
//     size_t old_size = size;

//     array = new LinkedList<HashMapEntry<K, V>>*[new_size];
//     size = new_size;

//     for (size_t i = 0; i < old_size; ++i){
//         Node<HashMapEntry<K,V>>* current = old[i]->getHead();
//         while (current!= nullptr) {
//             insert(current->getData().key, current->getData().value);
//             current = current->getNext();
//         }
//         delete old[i];
//     }

//     delete[] old;

// }


//  
// HashMap<K, V>::HashMap(size_t size){
//     this->size = size;
//     this->array = new linkedlist::LinkedList<HashMapEntry<K, V>>*[size];
//     for (size_t i = 0; i < size; i++) {
//         this->array[i] = new linkedlist::LinkedList<HashMapEntry<K, V>>();
//     }
// }

//  
// HashMap<K, V>::HashMap(){
//     this->size = 10;
//     this->array = new linkedlist::LinkedList<HashMapEntry<K, V>>*[10];
//     for (size_t i = 0; i < 10; i++) {
//         this->array[i] = new linkedlist::LinkedList<HashMapEntry<K, V>>();
//     }
// }

 
~HashMap() {
    for (size_t i = 0; i < size; i++) {
        delete this->array[i];
    }
    delete[] this->array;
}

//! Q3
 
bool insert(const K& key, const V& value) {
    size_t index = hash(key);
    linkedlist::Node<K, V> newNode(key, value);

    if (array[index]->containsItem(key, value)) {
        linkedlist::Node<K, V>* currentNode = array[index]->getHead();
        while (currentNode != nullptr) {
            if (currentNode->key == key && currentNode->value == value) {
                currentNode->value = value; // Update the value
                return true; // Key already existed
            }
            currentNode = currentNode->next;
        }
    } else {
        array[index]->insertAtTail(newNode);
    }
    return false; // Key didn't exist
}

//! Q4
 
V get(const K& key) const {
    size_t index = hash(key);

    linkedlist::Node<K, V>* currentNode = array[index]->getHead();
    while (currentNode != nullptr) {
        if (currentNode->key == key) {
            return currentNode->value;
        }
        currentNode = currentNode->next;
    }
        throw std::runtime_error("Key not found in HashMap");
}

 
bool remove(const K& key) {
    size_t index = hash(key);

    for (size_t i = 0; i < array[index].length(); ++i){
        if (array[index][i].key == key) {
            array[index].removeAt(i);
            return true;
        }
    }

    return false;
}

 
bool contains(const K& key) {
    size_t index = hash(key);
    return array[index]->containsKey(key);
}

 
size_t len(){
    size_t count = 0;

    for (size_t i = 0; i < size; ++i){
        count += array[i].length();
    }

    return count;
}


bool isEmpty(){
    return len() == 0;
}

// template <class K, class V>
// void HashMap<K, V>::print() {
//     for (size_t i = 0; i < size; ++i) {
//         linkedlist::LinkedList<HashMapEntry<K, V>>& currentList = array[i];
//         if (!currentList.isEmpty()){
//             std::cout << "List" << i << ": ";
//             currentList.printList();
//             std::cout << std::endl;
//         }
//     }
// }
};





#endif // HASHMAP_H


