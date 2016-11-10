#include "scope_exit.hpp"
#include <iostream>

int main()
{
    scope_exit { std::cout << "Everything is working correctly\n"; };
}
