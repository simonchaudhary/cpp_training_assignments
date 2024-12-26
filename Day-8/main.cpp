#include <iostream>
#include <variant>
#include <string>

int main() {
    // Define a variant that can hold an int, double, or std::string
    std::variant<int, double, std::string> var;

    // Assign different types to the variant
    var = 42;                     // Holds an int
    std::cout << "Integer: " << std::get<int>(var) << "\n";

    var = 3.14;                   // Holds a double
    std::cout << "Double: " << std::get<double>(var) << "\n";

    var = "Hello, World!";        // Holds a string
    std::cout << "String: " << std::get<std::string>(var) << "\n";

    return 0;
}
