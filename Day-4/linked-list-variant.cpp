#include "./linked-list-variant.hpp"

#include "../include/common/DataType.hpp"
#include "../include/common/variant/Variant.cpp"

// Append function implementation
void LinkedList::m_append(const Variant &value)
{

    Node *newNode = new Node(value);

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
LinkedList::~LinkedList()
{
    Node *temp = m_head;

    while (temp != nullptr)
    {
        // Store the next node
        Node *next = temp->m_next;
        delete temp;
        temp = next;
    }
}

std::ostream &operator<<(std::ostream &os, const LinkedList &list)
{
    Node *temp = list.m_head;

    temp->m_data.m_getDataType();

    while (temp != nullptr)
    {
        switch (temp->m_data.m_getDataType())
        {
        case DataType::INTEGER:
            os << "[" << temp->m_data.m_getIntegerValue() << " " << &temp->m_data << "] " << "[ " << &temp->m_next->m_data << " ]";
            break;
        case DataType::DOUBLE:
            os << "[" << temp->m_data.m_getDoubleValue() << " " << &temp->m_data << "] " << "[ " << &temp->m_next->m_data << " ]";
            break;
        case DataType::STRING:
            os << "[" << temp->m_data.m_getStringValue() << " " << &temp->m_data << "] " << "[ " << &temp->m_next->m_data << " ]";
            break;
        default:
            os << "Unknown type";
        }

        os << " -> ";

        temp = temp->m_next;
    }

    os << "nullptr";

    return os;
}

int main()
{
    LinkedList list;

    list.m_append(Variant(10));
    list.m_append(Variant(20.5));
    list.m_append(Variant("Hello"));
    // list.m_append(10);
    // list.m_append(20.5);
    // list.m_append("Hello");

    std::cout << list << '\n';

    return 0;
}
