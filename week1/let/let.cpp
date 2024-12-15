#include "let.hpp"

// Constructor for integer
Let::Let(int value) : m_integerValue(value), m_type(DATATYPE::INTEGER)
{
    cout << "This is integer constructor " << m_integerValue << " " << value << '\n';
}

// Constructor for double
Let::Let(double value) : m_doubleValue(value), m_type(DATATYPE::DOUBLE)
{
}

// Constructor for string
Let::Let(const char *value) : m_type(DATATYPE::STRING)
{
    cout << "This is string constructor" << *value << '\n';

    m_stringValue = new char[strlen(value) + 1];

    strcpy(m_stringValue, value);
}

// Copy Constructor
Let::Let(const Let &let) : m_type(let.m_type)
{
    cout << "This is copy constructor" << '\n';

    if (m_type == DATATYPE::INTEGER)
    {
        m_integerValue = let.m_integerValue;
    }

    else if (m_type == DATATYPE::DOUBLE)
    {
        m_doubleValue = let.m_doubleValue;
    }

    else if (m_type == DATATYPE::STRING)
    {
        // Deep copy
        m_stringValue = new char[strlen(let.m_stringValue) + 1];

        strcpy(m_stringValue, let.m_stringValue);
    }
};

// Copy Assignment Operator
Let &Let::operator=(const Let &let)
{
    cout << "This is copy assignment operator " << '\n';

    // Check self assignment
    if (this == &let)
    {
        cout << "same" << "\n";
        return *this;
    }

    cout << "diff" << "\n";

    m_type = let.m_type;

    if (m_type == DATATYPE::INTEGER)
    {
        cout << m_integerValue << '\n';
        cout << let.m_integerValue << '\n';

        m_integerValue = let.m_integerValue;
    }

    else if (m_type == DATATYPE::DOUBLE)
    {
        m_doubleValue = let.m_doubleValue;
    }

    else if (m_type == DATATYPE::STRING)
    {
        delete[] m_stringValue;

        // Deep copy
        m_stringValue = new char[strlen(let.m_stringValue) + 1];

        strcpy(m_stringValue, let.m_stringValue);
    }

    return *this;
}

// Move constructor
Let::Let(Let &&let) noexcept : m_type(let.m_type)
{
    cout << "Move constructor" << '\n';

    if (m_type == DATATYPE::INTEGER)
    {
        m_integerValue = let.m_integerValue;
    }

    else if (m_type == DATATYPE::DOUBLE)
    {
        m_doubleValue = let.m_doubleValue;
    }

    else if (m_type == DATATYPE::STRING)
    {
        m_stringValue = let.m_stringValue;

        let.m_stringValue = nullptr;
    }
}

//  Move assignment operator
Let &Let::operator=(Let &&let) noexcept
{
    cout << "Move assignment operator\n";

    // Check self-assignment
    if (this == &let)
        return *this;

    m_type = let.m_type;

    if (m_type == DATATYPE::INTEGER)
    {
        m_integerValue = let.m_integerValue;
    }

    else if (m_type == DATATYPE::DOUBLE)
    {
        m_doubleValue = let.m_doubleValue;
    }

    else if (m_type == DATATYPE::STRING)
    {
        delete[] m_stringValue;

        m_stringValue = let.m_stringValue;

        let.m_stringValue = nullptr;
    }

    return *this;
}

// == operator overloading
bool Let::operator==(const Let &let) const
{
    // Return false if type doesn't match
    if (m_type != let.m_type)
    {
        return false;
    }

    if (m_type == DATATYPE::INTEGER)
    {
        return m_integerValue == let.m_integerValue;
    }

    if (m_type == DATATYPE::DOUBLE)
    {
        return m_doubleValue == let.m_doubleValue;
    }

    if (m_type == DATATYPE::STRING)
    {
        cout << strcmp(m_stringValue, let.m_stringValue);

        return strcmp(m_stringValue, let.m_stringValue) == 0;
    }

    return false;
}

// Destructor
Let::~Let()
{

    if (m_type == DATATYPE::STRING)
    {
        delete[] m_stringValue;

        m_stringValue = nullptr;
    }
}

// Display method
void Let::m_display()
{
    if (m_type == DATATYPE::INTEGER)
    {
        cout << "This is integer value: " << m_integerValue << '\n';
    }

    else if (m_type == DATATYPE::DOUBLE)
    {
        cout << "This is double value: " << m_doubleValue << '\n';
    }

    else if (
        m_type == DATATYPE::STRING)
    {
        cout << "This is string value: " << m_stringValue << '\n';
    }
};
