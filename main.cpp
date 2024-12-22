#include <iostream>
#include <variant>
#include <string>

int main()
{
    std::variant<int, double, std::string> var = "Hello, Variant!";
    std::cout << std::get<std::string>(var) << std::endl;
    return 0;
}
