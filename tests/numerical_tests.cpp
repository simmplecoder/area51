#include "../src/numerical.hpp"
#include "../src/random_engine.hpp"
#include <cstddef>
#include <cassert>
#include <iostream>

constexpr std::size_t test_count = 1000;

template <typename T = int>
std::vector<T> generate_vector(std::size_t size)
{
    static shino::random_int_generator<> gen(0, 10'000);

    std::vector<T> v(size);
    gen(v.begin(), v.end());

    return v;
}

template <typename T, typename U>
auto handwritten_average(const std::vector<T>& input, U init = {})
{
    for (const auto& element: input)
    {
        init += element;
    }

    return init / input.size();
}

void test(std::size_t size)
{
    auto v = generate_vector(size);

    auto handwritten_result  = handwritten_average(v, 0.0);
    auto result = shino::average(v.begin(), v.end(), 0.0);

    assert(handwritten_result == result);
}

void run_tests()
{
    static shino::random_int_generator<std::size_t> gen(100, 10'000);

    for (std::size_t i = 0; i < test_count; ++i)
    {
        test(gen());
    }
}

int main()
{
    run_tests();
}