#include "logger.hpp" // Include the header to access the class definition

void Logger::log(const string &message)
{ // Definition of the log method
    cout << "[LOG] " << message << '\n';
}
