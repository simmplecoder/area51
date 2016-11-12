#include "scope_exit.hpp"
#include <iostream>
#include "string_manip.hpp"
#include "iterator.hpp"

int main()
{
    using shino::operator*;
    std::string s(1, 'a');
    shino::append_iterator<std::string, std::string> it(s);
    auto multiplied = s * 1024;
    std::cout << multiplied;
}
