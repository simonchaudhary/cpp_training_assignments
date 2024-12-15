#ifndef LET_H
#define LET_H

#include <iostream>
#include <cstring>

#include "../logger/logger.cpp"

using std::cout;

using std::move;

// Define DATATYPE enum class
enum class DATATYPE
{
    INTEGER,
    DOUBLE,
    STRING
};

class Let
{
public:
    // Constructor for integer
    Let(int value = 0);

    // Constructor for double
    Let(double value);

    // Constructor for string
    Let(const char *value);

    // Copy Constructor
    Let(const Let &let);

    // Copy Assignment Operator
    Let &operator=(const Let &let);

    // Move constructor
    Let(Let &&let) noexcept;

    //  Move assignment operator
    Let &operator=(Let &&let) noexcept;

    // == operator overloading
    bool operator==(const Let &let) const;

    // Destructor
    ~Let();

    // Display method
    void m_display();

private:
    int m_integerValue = 0;
    double m_doubleValue = 0.00;
    char *m_stringValue;
    DATATYPE m_type;
};

#endif
