#include "../src/circular_buffer.hpp"
#include <iostream>
#include <cassert>

void emplace_tests()
{
    shino::circular_buffer<std::size_t> buffer(10);

    for (std::size_t i = 0; i < 15; ++i)
    {
        buffer.emplace(i);
    }

    for (std::size_t i = 0; i < 5; ++i)
    {
        assert(buffer[i] == i + 10);
    }

    for (std::size_t i = 5; i < 10; ++i)
    {
        assert(buffer[i] == i);
    }
}

void pop_tests()
{
    shino::circular_buffer<std::size_t> buffer(10);

    for (std::size_t i = 0; i < 5; ++i)
    {
        buffer.emplace(i);
    }

    std::cout << "emplaced 5 elements: " << buffer << '\n';

    for (std::size_t i = 0; i < 3; ++i)
    {
        buffer.pop();
    }

    std::cout << "popped 3 elements: " << buffer << '\n';

    for (std::size_t i = 0; i < 5; ++i)
    {
        buffer.emplace(i);
    }

    std::cout << "emplaced 5 more elements: " << buffer << '\n';

    for (std::size_t i= 3; i < 5; ++i)
    {
        assert(buffer[i] == i);
    }

    for (std::size_t i = 5; i < 10; ++i)
    {
        assert(buffer[i] == i - 5);
    }
}



int main()
{
    emplace_tests();
    pop_tests();
}

