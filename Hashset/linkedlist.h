#include <stdio.h>
#include <stdbool.h>
#include "llnode.h"
#include <stdlib.h>

#pragma once

namespace linkedlist
{ 

    template <class T>
    class LinkedList
    {
    private:
        linkedlist::Node<T> *head;
        linkedlist::Node<T> *tail;

    public:
        size_t length;
        LinkedList();
        ~LinkedList();
        size_t insertAtTail(T item);
        size_t insertAtHead(T item);
        size_t insertAtIndex(size_t index, T item);
        T removeTail();
        void printList();
        bool removeHead();
        bool removeAtIndex(size_t index);
        bool containsItem(T item);
        T itemAtIndex(int index);
        bool remove(T item);
        linkedlist::Node<T>* getHead(); //! Added this to get the head of the linkedlist
    };

}
