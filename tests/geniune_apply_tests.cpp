#include "../src/utilities.hpp"
#include <stdexcept>

int dummy_x(const std::tuple<int, int>&)
{
    return 1;
}

int dummy_y(int y)
{
    return y;
}

void check(int retvalue, int expectedvalue)
{
    if (retvalue != expectedvalue)
    {
        throw std::logic_error("geniune apply doesn't return the correct value");
    }


}

int main()
{
    int res = 0;
    res = shino::genuine_apply(dummy_x, std::make_tuple(std::tuple<int, int>(1, 1)));
    check(res, 1);

    res = shino::genuine_apply(dummy_y, 1);
    check(res, 1);

    shino::genuine_apply(dummy_y, std::make_tuple(1));
    check(res, 1);
}

