#ifndef LLNODE_H
#define LLNODE_H

namespace linkedlist{

template <class K, class V>
class Node {
public:
    K key;
    V value;
    linkedlist::Node<K, V>* next;
    Node();
    Node(const K& key, const V& value);
    ~Node();
};

    template <class K, class V>
    Node<K, V>::Node()
    {
        this->next = NULL;
    }

    
    template <class K, class V>
    Node<K, V>::Node(const K& key, const V& value)
    {
        this->key = key;
        this->value = value;
        this->next = NULL;
    }
    template <class K, class V>
    Node<K, V>::~Node()
    {

    }
}
#endif 
