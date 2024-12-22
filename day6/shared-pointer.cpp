
#include <iostream>

using std::cout;

template <typename T>
class SharedPointer
{
public:
    // Constructor
    explicit SharedPointer(T *sp = nullptr) : m_value(sp), m_counter(nullptr)
    {
        if (sp)
        {
            m_counter = new int(1); // Initialize reference count to 1
            cout << "Constructor: Counter = " << *m_counter << "\n";
        }
    }

    // Copy Constructor
    SharedPointer(const SharedPointer &sp) : m_value(sp.m_value), m_counter(sp.m_counter)
    {
        if (m_counter)
        {
            (*m_counter)++; // Increment the reference count
            cout << "Copy Constructor: Counter = " << *m_counter << "\n";
        }
    }

    // Copy Assignment Operator
    SharedPointer &operator=(const SharedPointer &sp)
    {
        if (this != &sp) // Avoid self-assignment
        {
            release(); // Release current resources

            // Copy data from the other SharedPointer
            m_value = sp.m_value;
            m_counter = sp.m_counter;

            if (m_counter)
            {
                (*m_counter)++; // Increment reference count
                cout << "Assignment Operator: Counter = " << *m_counter << "\n";
            }
        }
        return *this;
    }

    // Destructor
    ~SharedPointer()
    {
        release();
    }

    // Utility functions
    void getPointer() const
    {
        if (m_value)
            cout << "Managed Object Value: " << *m_value << "\n";
        else
            cout << "No Managed Object\n";
    }

    void getCounter() const
    {
        if (m_counter)
            cout << "Counter: " << *m_counter << "\n";
        else
            cout << "No Counter\n";
    }

private:
    T *m_value;     // Pointer to the managed object
    int *m_counter; // Pointer to the reference count

    void release()
    {
        if (m_counter) // If reference count exists
        {
            (*m_counter)--; // Decrement the reference count
            cout << "Destructor: Counter = " << *m_counter << "\n";

            if (*m_counter == 0) // If no more owners
            {
                cout << "Destructor: Deleting managed object and counter\n";
                delete m_value;   // Free the managed object
                delete m_counter; // Free the counter
            }
        }
    }
};

int main()
{
    cout << "Creating sp1\n";
    SharedPointer<int> sp1(new int(55)); // sp1 manages the object
    sp1.getPointer();
    sp1.getCounter();

    cout << "\nCopying sp1 to sp2\n";
    SharedPointer<int> sp2 = sp1; // Copy constructor
    sp2.getPointer();
    sp2.getCounter();

    cout << "\nAssigning sp1 to sp3\n";
    SharedPointer<int> sp3;
    sp3 = sp1; // Assignment operator
    sp3.getPointer();
    sp3.getCounter();

    cout << "\nEnd of main\n";
    return 0;
}
