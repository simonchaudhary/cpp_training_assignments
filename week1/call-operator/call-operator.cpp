#include <iostream>

using std::cout;

class Add
{
public:
    //
    Add(int value) : m_value(value) {}

    // Overloading call operator (operator())
    int operator()(int value)
    {
        return m_value + value;
    }

private:
    // Private member variable to  store initial value
    int m_value;
};

int main()
{
    // Create an instance of Add class.
    Add add(5);

    // Call operator can be invoked explicitly;
    std::cout << add.operator()(20) << '\n';

    // Call operator can be invoked implicitly;
    std::cout << add(5) << '\n';
}
