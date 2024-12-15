#include "let.cpp"

int main()
{
    // Integer instance
    Let integerValue = 1;

    integerValue.m_display();

    // Double instance
    Let doubleValue = 12.222;

    doubleValue.m_display();

    // String instance
    Let stringValue = "Hello world";

    // Call copy constructor
    Let stringValue1 = stringValue;

    Let stringValue2 = "Copy";

    // Self assignment
    stringValue1 = stringValue1;

    // Call copy assignment operator
    stringValue2 = stringValue;

    // Call move constructor
    Let stringValue3 = move(stringValue1);

    // Call move assignment operator
    Let stringValue4 = "Move operator";
    stringValue4 = move(stringValue3);

    // += Operator
    Let concatValue = "Hello ";
    concatValue += "World";

    concatValue.m_display();

    // == Operator
    Let compareValueA = "Hello";
    Let compareValueB = "Hello";

    if (compareValueA == compareValueB)
    {
        cout << "Both value is same\n";
    }
    else
    {
        cout << "Both value is different\n";
    }
}
