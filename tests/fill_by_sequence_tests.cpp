#include <algorithm.hpp>

#include <numeric>
#include <iostream>
#include <stdexcept>
#include <array>

void compare_to_iota()
{
    std::array<int, 20> v1 = {};
    shino::fill_by_sequence(v1.begin(), v1.end());

    std::array<int, 20> v2 = {};
    std::iota(v2.begin(), v2.end(), 0);

    bool equal = std::equal(v1.begin(), v1.end(), v2.begin());
    if (!equal)
    {
        throw std::logic_error("output of iota and fill_by_sequence don't match");
    }
}

void generate_powers_of_two()
{
    std::array<int, 10> powers_of_two;

    shino::fill_by_sequence(powers_of_two.begin(), powers_of_two.end(),
                            1, shino::inplace_multiply_by<>(2));

    if (powers_of_two[0] != 1)
    {
        throw std::logic_error("fill_by_sequence doesn't correctly set first element");
    }

    for (std::size_t i = 1; i < powers_of_two.size(); ++i)
    {
        if (powers_of_two[i - 1] * 2 != powers_of_two[i])
        {
            throw std::logic_error("fill_by_sequence doesn't correctly mutate the initvalue");
        }
    }
}

int main()
{
    compare_to_iota();
    generate_powers_of_two();
    std::cout << "all tests passed";
}

