#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>
#include "../include/common/variant/Variant.hpp"

// Node structure
struct Node
{
    Variant m_data;
    Node *m_next;

    // Constructor
    Node(const Variant &value) : m_data(value), m_next(nullptr) {}
};

// LinkedList class
class LinkedList
{

public:
    // Constructor
    LinkedList() : m_head(nullptr), m_tail(nullptr) {}

    // Append a value to the list
    void m_append(const Variant &value);

    // Friend function to display the linked list
    friend std::ostream &operator<<(std::ostream &os, const LinkedList &list);

    // Destructor
    ~LinkedList();

private:
    Node *m_head;
    Node *m_tail;
};

#endif // LINKED_LIST_HPP
