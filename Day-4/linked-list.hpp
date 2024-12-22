#include "../include/common/CommonHeader.hpp"

// Node structure
template <typename T>
struct Node
{
    T m_data;
    Node *m_next;

    Node(T value) : m_data(value), m_next(nullptr) {}
};

template <typename T>
class LinkedList
{

public:
    // Append function
    void m_append(T value);

    // Friend function for overloading <<
    template <typename U>
    friend std::ostream &operator<<(std::ostream &stream, const LinkedList<U> &ll);

    // Destructor
    ~LinkedList();

private:
    Node<T> *m_head = nullptr;
    Node<T> *m_tail = nullptr;
};
