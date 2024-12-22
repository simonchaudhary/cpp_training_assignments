#ifndef VARIANT_HPP
#define VARIANT_HPP

#include <cstring>

#include "../DataType.hpp"
#include "../CommonHeader.hpp"

class Variant
{
public:
    // Constructors
    Variant(int value);
    Variant(double value);
    Variant(bool value);
    Variant(const char *value);

    // Copy Constructor
    // Variant(const Variant &variant);

    // Member functions
    int m_getIntegerValue();
    double m_getDoubleValue();
    bool m_getBooleanValue();
    char m_getStringValue();
    void m_display();
    DataType m_getDataType();

    // Destructor
    ~Variant();

private:
    // Member variables
    int m_integerValue = 0;
    double m_doubleValue = 0.00;
    bool m_boolValue = false;
    char *m_stringValue = nullptr;
    DataType m_type;
};

#endif // VARIANT_HPP
