#include "../src/iterator.hpp"
#include "../src/random_int_generator.hpp"
#include <vector>
#include <string>
#include <cassert>
#include <iostream>

template <typename T = int>
std::vector<T> generate_vector(std::size_t size)
{
    static shino::random_int_generator<> gen(0, 100);
    std::vector<T> v(size);
    gen(v.begin(), v.end());

    return v;
}

void int_addition_test()
{
    std::vector<int> correct_answer;

    int num = 3;
    constexpr std::size_t copy_count = 100;
    for (std::size_t i = 0; i < copy_count; ++i)
    {
        correct_answer.push_back(num);
    }
    std::vector<int> v(copy_count);
    shino::stumbled_iterator<int> first(num, copy_count);

    std::copy(first, shino::stumbled_iterator<int>{}, v.begin());
    assert(correct_answer == v);
}

void string_adding_test()
{
    const std::string value = "a";

    constexpr std::size_t copy_count = 100;
    std::vector<std::string> v(100);
    auto correct_answer = v;
    for (std::size_t i = 0; i < copy_count; ++i)
    {
        correct_answer[i] = value;
    }

    shino::stumbled_iterator<std::string> first(value, 100);
    std::copy(first, shino::stumbled_iterator<std::string>{}, v.begin());

    if (v != correct_answer)
    {
        std::cerr << "string adding test: answers don't match\n";
        throw std::exception();
    }
}

void run_tests()
{
    int_addition_test();
    string_adding_test();
}

int main()
{
    run_tests();
}