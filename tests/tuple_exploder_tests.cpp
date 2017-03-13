#include "../src/explode_tuple.hpp"
#include <string>
#include <iostream>
#include <utility>
#include <array>

int func(int, char, std::string&)
{
    return 0;
}

int add(int x, int y)
{
    return x + y;
}

int main()
{
    std::tuple<int, char, std::string> t(2, '2', "2");
    std::cout << explode(&func, t) << '\n';
    std::cout << explode(&add, std::make_tuple(1, 2)) << '\n';

    std::array<int, 2> arr = {1, 2};
    std::cout << explode(&add, arr);
}