#include <cstring>

#include <iostream>

using std::cout;

enum class DataType
{
    INTEGER,
    DOUBLE,
    STRING
};

class Variant
{
public:
    // Copy Constructor
    Variant(const Variant &variant) : m_type(variant.m_type)
    {
        cout << "Copy constructor\n";

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
    };

    Variant(int value = 9) : m_integerValue(value), m_type(DataType::INTEGER) {};

    Variant(double value = 0.39) : m_doubleValue(value), m_type(DataType::DOUBLE) {};

    Variant(const char *value = "CHAU") : m_type(DataType::STRING)
    {
        m_stringValue = new char[strlen(value) + 1];

        strcpy(m_stringValue, value);
    };

    int getIntegerValue()
    {
        return m_integerValue;
    }

    char *getStringValue()
    {
        return m_stringValue;
    }

    int getDoubleValue()
    {
        return m_doubleValue;
    }

    DataType getDataType()
    {
        return m_type;
    }

    ~Variant()
    {
        if (m_type == DataType::STRING)
        {
            delete[] m_stringValue;
        }
    }

private:
    int m_integerValue = 0;
    double m_doubleValue = 0.00;
    char *m_stringValue;
    DataType m_type;
};
