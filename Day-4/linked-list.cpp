#include "./linked-list.hpp"

// Append function implementation
template <typename T>
void LinkedList<T>::m_append(T value)
{
    cout << "Appending value: " << value << "\n";
    Node<T> *newNode = new Node<T>(value);

    // Initially head is nullptr
    if (m_head == nullptr)
    {
        m_head = newNode;
        m_tail = newNode;
    }
    else
    {
        // New node added to tail
        m_tail->m_next = newNode;
        m_tail = newNode;
    }
}

// Destructor implementation
template <typename T>
LinkedList<T>::~LinkedList()
{
    Node<T> *temp = m_head;

    while (temp != nullptr)
    {
        // Store the next node
        Node<T> *next = temp->m_next;
        delete temp;
        temp = next;
    }
}

template <typename U>
std::ostream &operator<<(std::ostream &os, const LinkedList<U> &list)
{
    Node<U> *temp = list.m_head;

    while (temp != nullptr)
    {
        os << temp->m_data << " -> ";
        temp = temp->m_next;
    }

    os << "nullptr";

    return os;
}

int main()
{
    LinkedList<std::string> list;

    // list.m_append(10);
    // list.m_append(20);
    // list.m_append(30);

    list.m_append("Simon");
    list.m_append("Simon2");
    list.m_append("Simon3");

    std::cout << list << '\n';

    return 0;
}
