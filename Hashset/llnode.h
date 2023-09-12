#pragma once

namespace linkedlist
{
    template <class T>
    class Node
    {
    public:
        T item;
        size_t length;
        linkedlist::Node<T> *next;
        Node();
        Node(T item);
        ~Node();
    };
}
