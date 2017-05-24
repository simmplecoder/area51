#include "../src/random_int_generator.hpp"
#include <iostream>

int main()
{
    shino::random_int_generator<> gen(0, 100);
    auto range = gen.range();

    std::cout << "Generating random number in ["
              << range.first << ' ' << range.second << ")\n";

    for (int i = 0; i < 10; ++i)
    {
        std::cout << gen() << ' ';
    }
    std::cout << '\n';

    gen.range(0, 10);
    range = gen.range();
    std::cout << "Changing range to ["
              << range.first << ' ' << range.second
              << ") and generating again\n";

    for (int i = 0; i < 10; ++i)
    {
        std::cout << gen() << ' ';
    }
}

