#include "Variant.hpp"

// Constructor for int
Variant::Variant(int value) : m_integerValue(value), m_type(DataType::INTEGER) { cout << "Integer:" << "\n"; }

// Constructor for double
Variant::Variant(double value) : m_doubleValue(value), m_type(DataType::DOUBLE) {}

// Constructor for bool
Variant::Variant(bool value) : m_boolValue(value), m_type(DataType::BOOLEAN) {}

// Constructor for string
Variant::Variant(const char *value) : m_type(DataType::STRING)
{
    m_stringValue = new char[strlen(value) + 1];
    strcpy(m_stringValue, value);
}

// Copy Constructor
Variant::Variant(const Variant &variant) : m_type(variant.m_type)
{
    std::cout << "Copy constructor\n";
    if (m_type == DataType::INTEGER)
    {
        m_integerValue = variant.m_integerValue;
    }
    else if (m_type == DataType::DOUBLE)
    {
        m_doubleValue = variant.m_doubleValue;
    }
    else if (m_type == DataType::STRING)
    {
        m_stringValue = new char[strlen(variant.m_stringValue) + 1];
        strcpy(m_stringValue, variant.m_stringValue);
    }
}

int Variant::m_getIntegerValue()
{
    return m_integerValue;
}

double Variant::m_getDoubleValue()
{
    return m_doubleValue;
}

bool Variant::m_getBooleanValue()
{
    return m_boolValue;
}

char Variant::m_getStringValue()
{
    return *m_stringValue;
}

// Member function definitions
void Variant::m_display()
{
    if (m_type == DataType::INTEGER)
    {
        cout << "This is integer value: " << m_integerValue << '\n';
    }

    else if (m_type == DataType::DOUBLE)
    {
        cout << "This is double value: " << m_doubleValue << '\n';
    }

    else if (m_type == DataType::BOOLEAN)
    {
        cout << "This is boolean value: " << m_doubleValue << '\n';
    }

    else if (
        m_type == DataType::STRING)
    {
        cout << "This is string value: " << m_stringValue << '\n';
    }
}

// Get data type
DataType Variant::m_getDataType()
{
    return m_type;
}

// Destructor
Variant::~Variant()
{
    if (m_type == DataType::STRING)
    {
        delete[] m_stringValue;
    }
}

// int main()
// {
//     Variant v(20);
//     v.m_display();
// }
