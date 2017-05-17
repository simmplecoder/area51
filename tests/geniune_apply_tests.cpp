#include "../src/utilities.hpp"
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

int dummy_x(const std::tuple<int, int>&)
{
    return 1;
}

int dummy_y(int y)
{
    return y;
}

int main()
{
    shino::geniune_apply(&dummy_x, std::make_tuple(std::tuple<int, int>(1, 1)));
    shino::geniune_apply(dummy_y, 1);
    shino::geniune_apply(dummy_y, std::make_tuple(1));
}

