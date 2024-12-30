#include <iostream>

using std::cout;

using namespace std;

int main()
{
    // Dynamically  allocated memory
    int *value = new int(22);

    cout << "Value is assigned: " << *value << '\n';

    // Memory is free.
    delete value;

    // Pointer *value is dangling pointer

    // Dereferencing the *value can lead to garbage value or crash
    // This is Undefined behaviour
    cout << "Value is deleted: " << *value << '\n';

    // To Handle dangling pointer
    // Assign *value pointer to nullptr
    value = nullptr;

    // Checking if *value pointer  is null pointer
    if (!value)
    {
        cout << "Value pointer is now a null pointer." << endl;
    }

    return 0;
}
