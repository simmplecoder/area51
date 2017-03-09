#include "../src/tuple_exploder.hpp"
#include <string>
#include <iostream>
#include <utility>
#include <experimental/tuple>
#include <experimental/functional>

int func(int x, char y, std::string& s)
{
    return 0;
}

int main()
{
    std::tuple<int, char, std::string> t(2, '2', "2");
}