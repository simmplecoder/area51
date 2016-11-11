#include "scope_exit.hpp"
#include <iostream>
#include "string_manip.hpp"
#include "iterator.hpp"

int main()
{
    using namespace shino;
    std::string s;
    shino::append_iterator<std::string, std::string> it(s);
    *it = "abc";
    *it = "cde";
    std::cout << s;
}
