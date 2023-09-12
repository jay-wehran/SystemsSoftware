#include "../include/hashset.hpp"
#include "../linkedlist/linkedlist.h"
#include <iostream>

using namespace linkedlist;

template <class T>
HashSet<T>::HashSet(size_t size)
{
    //!
    this->size = size;
    this->array = new linkedlist::LinkedList<int> *[size];

    //!
    for (size_t i = 0; i < size; ++i)
    {
        array[i] = new linkedlist::LinkedList<int>();
    }
}

template <class T>
HashSet<T>::~HashSet()
{
    //!
    for (size_t i = 0; i < size; ++i)
    {
        delete array[i];
    }
    delete[] array;
}

    template <class T>
    unsigned long HashSet<T>::hash(int item)
    {
        //!
        unsigned long prehashed = prehash(item);
        return prehashed % this->size;
    }


    template <class T>
    bool HashSet<T>::insert(int item)
    {
        //!
        unsigned long index = hash(item);
        if (array[index]->containsItem(item)) {
            return false;
        }
        

        //!
        size_t totalItems = len();
        size_t emptyBuckets = capacity();
        double loadFactor = static_cast<double>(totalItems) / (totalItems + emptyBuckets);

        if (loadFactor > 0.7) {
             //!
            size_t newSize = size * 2;
            linkedlist::LinkedList<int> **newArray = new linkedlist::LinkedList<int> *[newSize];
            for (size_t i = 0; i < newSize; ++i)
            {
                newArray[i] = new linkedlist::LinkedList<int>();
            }
            for (size_t i = 0; i < size; ++i)
            {
                linkedlist::Node<int> *current = array[i]->getHead();
                while (current != nullptr)
                {
                    if (current->item == item) {
                        return false; //checking if the current item already exists in the hashset
                    }
                    unsigned long newIndex = prehash(current->item) % newSize;
                    newArray[newIndex]->insertAtTail(current->item);
                    current = current->next;
                }
            }
            //! deallocation 
            for (size_t i = 0; i < size; ++i)
            {
                delete array[i];
            }
            delete[] array;
            this->size = newSize;
            array = newArray;
        }

        //!
        bool isInserted = array[index]->insertAtTail(item);

        return isInserted;
    }

    template <class T>
    bool HashSet<T>::remove(int item)
    {
        //!
        unsigned long index = hash(item);
        if (contains(item) == false) {
            return false;
        }

        return this->array[index]->remove(item);
    }

    template <class T>
    bool HashSet<T>::contains(int item)
    {
        //!
        unsigned long index = hash(item);
        return array[index]->containsItem(item);
    }

    template <class T>
    size_t HashSet<T>::len()
    {
        //!
        size_t totalItems = 0;
        for (size_t i = 0; i < size; ++i)
        {
            totalItems += array[i]->length;
        }
        return totalItems;
    }

    template <class T>
    size_t HashSet<T>::capacity()
    {
        //!
        size_t emptyBuckets = 0;
        for (size_t i = 0; i < size; ++i)
        {
            if (array[i]->length == 0)
            {
                emptyBuckets++;
            }
        }
        return emptyBuckets;
    }

    template <class T>
    void HashSet<T>::print()
    {
        //!
        for (size_t i = 0; i < size; ++i)
        {
            std::cout << "Bucket " << i << ": ";
            array[i]->printList();
            std::cout << std::endl;
        }
    }

    //! Adding this method helped in retreiving the head of a LL
template <class T> 
    linkedlist::Node<T>* LinkedList<T>::getHead() {
        return this->head;
    }












//! LINKEDLIST IMPLEMENTATIONS
     template <class T>
    LinkedList<T>::LinkedList()
    {
        head = new Node<T>();
        tail = new Node<T>();
        this->head = NULL;
        this->tail = NULL;
        this->length = 0;
    }

    template <class T>
    LinkedList<T>::~LinkedList()
    {
        Node<T> *temp = this->head;
        while (temp != NULL)
        {
            Node<T> *t = temp;
            temp = temp->next;
            free(t);
        }
    }

    template <class T>
    size_t LinkedList<T>::insertAtTail(T item)
    {
        Node<T> *node = new Node<T>(item);
        if (node == NULL)
        {
            return 1;
        }
        // if list is empty.
        if (this->head == NULL)
        {
            this->head = node;
            this->tail = node;
        }
        else
        {
            this->tail->next = node;
            this->tail = this->tail->next;
        }
        this->length++;
        return true;
    }

    template <class T>
    bool LinkedList<T>::containsItem(T item)
    {
        Node<T> *current = this->head;
        while (current != nullptr) {
            if (current->item == item) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    template <class T>
    size_t LinkedList<T>::insertAtHead(T item)
    {
        Node<T> *node = new Node<T>(item);
        if (node == NULL)
        {
            return 1;
        }
        // if list is empty.
        if (this->head == NULL)
        {
            this->head = node;
            this->tail = node;
        }
        else
        {
            node->next = this->head;
            this->head = node;
        }
        this->length++;
        return 0;
    }

    template <class T>
    size_t LinkedList<T>::insertAtIndex(size_t index, T item)
    {
        if (index == 0)
        {
            return insertAtHead(item);
        }
        Node<T> *current = this->head;
        Node<T> *items = new Node<T>(item);
        if (items == NULL)
        {
            return 1;
        }
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        items->next = current->next;
        current->next = items;
        return 0;
    }

    template <class T>
    T LinkedList<T>::removeTail()
    {
        Node<T> *temp;
        int i = 0;
        T item;
        if (this->tail == NULL)
        {
            // List is Empty
            return 0;
        }
        else
        {
            temp = this->head;

            // Iterate to the end of the list
            while (temp->next != this->tail)
            {
                temp = temp->next;
            }

            item = this->tail->item;

            Node<T> *old_tail = this->tail;
            this->tail = temp;
            this->tail->next = NULL;
            free(old_tail);
        }
        this->length--;
        return item;
    }

    template <class T>
    bool LinkedList<T>::removeHead()
    {
        T item;
        if (this->head == NULL)
        {
            // List is Empty
            return 0;
        }
        else
        {
            item = this->head->item;
            Node<T> *old_head = this->head;
            this->head = this->head->next;
            free(old_head);
        }
        this->length--;
        return true;
    }

    template <class T>
    bool LinkedList<T>::remove(T item)
    {
        int index = -1;
        T temp = 0;
        Node<T> *current = this->head;
        for (int i = 0; i < this->length; i++)
        {
            index++;
            if (current->item == item)
            {
                temp = this->removeAtIndex(index);
                return true;
            }
            current = current->next;
            if (current == NULL)
            {
                break;
            }
        }
        return true;
    }

    template <class T>
    bool LinkedList<T>::removeAtIndex(size_t index)
    {
        if (index < 0 || index >= this->length)
        {
            return 0;
        }
        if (index == 0)
        {
            return removeHead();
        }
        if (index == length - 1)
        {
            return removeTail();
        }
        Node<T> *cN = this->head;
        size_t limit = this->length;
        for (size_t i = 0; i < limit; i++)
        {
            if (i + 1 == index)
            {
                T returnVal = cN->next->item;
                free(cN->next);
                cN->next = cN->next->next;
                this->length--;
                return true;
            }
        }
        return 0;
    }

    template <class T>
    T LinkedList<T>::itemAtIndex(int index)
    {

        Node<T> *current = this->head;
        for (int i = 0; i < index; i++)
        {
            if (current->next != NULL)
            {
                current = current->next;
            }
            else
            {
                exit(1);
            }
        }
        return current->item;
    }

    template <class T>
    void LinkedList<T>::printList()
    {
        size_t limit = this->length;
        if (!this->length)
        {
            printf("Empty");
        }
        Node<T> *cP = this->head;
        for (size_t i = 0; i < limit; i++)
        {
            printf("%d -> ", cP->item);
            cP = cP->next;
        }
    }

    template <class T>
    Node<T>::Node()
    {
        this->item = 0;
        this->next = NULL;
    }
    template <class T>
    Node<T>::Node(T item)
    {
        this->item = item;
        this->next = NULL;
    }
    template <class T>
    Node<T>::~Node()
    {
    }

    template <class T>
    linkedlist::Node<T>* LinkedList<T>::getHead() {
        return this->head;
    }
