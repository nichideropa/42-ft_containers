#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <ctime>


/* Helper Functions copied from the repository of Hepple42 on Github */


/* functor for comparison */
template <typename T>
struct compare_more : std::binary_function<T, T, bool>
{
    bool operator()(const T &lhs, const T &rhs) const
    {
        return lhs > rhs;
    }
};

template <typename T>
void print_line(const T line)
{
    std::cout << line << std::endl;
}

template <typename T>
void print_value(const std::string &name, const T& value)
{
    std::cout << name << ": " << value << std::endl;
}


void print_bool(const std::string &name, bool b)
{
    std::cout << name << ": ";
    if (b)
        std::cout << "true";
    else
        std::cout << "false";
    std::cout << std::endl;
}

void print_title(const std::string title)
{
    std::cout << title << std::endl << std::endl;
}

void print_separator()
{
    std::cout << "- - - - - - - - - - - - - - - - -" << std::endl;
}
