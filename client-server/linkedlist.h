#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdbool.h>
#include "llnode.h"
#include <stdlib.h>

namespace linkedlist{

// template <class K, class V>
// struct HashMapEntry{
//     K key;
//     V value;
// };

template <class K, class V>
class LinkedList {
  private:
    // linkedlist::
    Node<K, V>* head;
    // linkedlist::
    Node<K, V>* tail;
    size_t length;
  public:
    LinkedList();
    ~LinkedList();
    size_t insertAtTail(const Node<K, V>& node);
    size_t insertAtHead(const K& key, const V& value);
    size_t insertAtIndex(size_t index, const K& key, const V& value);
    V removeTail();
    void printList() const;
    V removeHead();
    V removeAtIndex(size_t index);
    bool containsItem(const K& key, const V& value) const;
    V itemAtIndex(int index);
    V remove(K item);
    size_t getLength() const;
    bool containsKey(const K& key) const;
    linkedlist::Node<K, V> *getHead() const;
};

    template <class K, class V>
    LinkedList<K, V>::LinkedList()
    {
        head = new Node<K, V>();
        tail = new Node<K, V>();
        this->head = nullptr;
        this->tail = nullptr;
        this->length = 0;
}

    template <class K, class V>
    LinkedList<K, V>::~LinkedList()
    {
        Node<K, V>* temp = this->head;
        while(temp!=NULL)
        {
            Node<K, V>* t = temp;
            temp = temp->next;
            free(t);
        }
    }



template <class K, class V>
size_t LinkedList<K, V>::insertAtTail(const Node<K, V>& node) {
    Node<K, V>* newNode = new Node<K, V>(node);
    if (newNode == nullptr) {
        return 1;
    }
    // if list is empty
    if (this->head == nullptr) {
        this->head = newNode;
        this->tail = newNode;
    } else {
        this->tail->next = newNode;
        this->tail = this->tail->next;
    }
    this->length++;
    return 0;
}

template <class K, class V>
bool LinkedList<K, V>::containsItem(const K& key, const V& value) const {
    Node<K, V>* current = this->head;
    for (int i = 0; i < this->length; i++) {
        if (current->key == key && current->value == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}


template <class K, class V>
size_t LinkedList<K, V>::insertAtHead(const K& key, const V& value) {
    Node<K, V>* node = new Node<K, V>(key, value);
    if (node == NULL) {
        return 1;
    }
    //if list is empty.
    if (this->head == NULL) {
        this->head = node;
        this->tail = node;
    } else {
        node->next = this->head;
        this->head = node;
    }
    this->length++;
    return 0;
}

template <class K, class V>
size_t LinkedList<K, V>::insertAtIndex(size_t index, const K& key, const V& value) {
    if (index == 0) {
        return insertAtHead(key, value);
    }
    Node<K, V>* current = this->head;
    Node<K, V>* items = new Node<K, V>(key, value);
    if (items == NULL) {
        return 1;
    }
    for (size_t i = 0; i < index - 1; i++) {
        current = current->next;
    }
    items->next = current->next;
    current->next = items;
    this->length++;
    return 0;
}

template <class K, class V>
V LinkedList<K, V>::removeTail() {
    Node<K, V>* temp;
    V item;
    if (this->tail == NULL) {
        // List is Empty
        return V();  // Return a default-constructed value for V
    } else {
        temp = this->head;

        // Iterate to the end of the list
        while (temp->next != this->tail) {
            temp = temp->next;
        }

        item = this->tail->item;

        Node<K, V>* old_tail = this->tail;
        this->tail = temp;
        this->tail->next = NULL;
        delete old_tail;
    }
    this->length--;
    return item;
}

template <class K, class V>
V LinkedList<K, V>::removeHead() {
    V item;
    if (this->head == NULL) {
        // List is Empty
        return V();  // Return a default-constructed value for V
    } else {
        item = this->head->item;
        Node<K, V>* old_head = this->head;
        this->head = this->head->next;
        delete old_head;
    }
    this->length--;
    return item;
}

template <class K, class V>
V LinkedList<K, V>::remove(K item) {
    int index = -1;
    V temp = V();
    Node<K, V>* current = this->head;
    for (int i = 0; i < this->length; i++) {
        index++;
        if (current->key == item) {
            temp = this->removeAtIndex(index);
            return temp;
        }
        current = current->next;
        if (current == NULL) {
            break;
        }
    }
    return temp;
}

template <class K, class V>
V LinkedList<K, V>::removeAtIndex(size_t index) {
    if (index < 0 || index >= this->length) {
        return V();  // Default-constructed value for V
    }
    if (index == 0) {
        return removeHead();
    }
    if (index == length - 1) {
        return removeTail();
    }
    Node<K, V>* cN = this->head;
    size_t limit = this->length;
    for (size_t i = 0; i < limit; i++) {
        if (i + 1 == index) {
            V returnVal = cN->next->item;  // Value of type V
            delete cN->next;
            cN->next = cN->next->next;
            this->length--;
            return returnVal;
        }
    }
    return V();  // Default-constructed value for V
}


template <class K, class V>
V LinkedList<K, V>::itemAtIndex(int index) {
    Node<K, V>* current = this->head;
    for (int i = 0; i < index; i++) {
        if (current->next != NULL) {
            current = current->next;
        } else {
            throw std::out_of_range("Index out of bounds");
        }
    }
    return current->item;
}


template <class K, class V>
void LinkedList<K, V>::printList() const{
    size_t limit = this->length;
    if (!this->length) {
        printf("Empty");
    }
    Node<K, V>* cP = this->head;
    for (size_t i = 0; i < limit; i++) {
        printf("(%s, ... ) -> ", cP->item.key.c_str());
        cP = cP->next;
    }
}

template <class K, class V>
size_t LinkedList<K, V>::getLength() const {
    return length;
}

template <class K, class V>
bool LinkedList<K, V>::containsKey(const K& key) const {
    Node<K, V>* current = this->head;
    while (current != nullptr) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <class K, class V>
linkedlist::Node<K, V>* LinkedList<K, V>::getHead() const {
    return head;
}
    
}



#endif // LINKEDLIST_H
