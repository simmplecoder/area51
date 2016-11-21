#include "iterator.hpp"
#include <string>
#include <iostream>

int main()
{
    std::string str;
    shino::append_iterator<std::string, std::string> appiterator(str);
    for (std::size_t i = 0; i < 5; ++i)
    {
        *appiterator = "abc";
        ++appiterator;
    }

    std::cout << str;
}
