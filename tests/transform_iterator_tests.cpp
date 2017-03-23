//
// Created by olzhas on 2/18/17.
//

#include "../src/transform_iterator.hpp"
#include "../src/random_engine.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <cstddef>
#include <cassert>
#include <functional>
#include <iostream>

template <typename T = int>
std::vector<T> generate_randomized_vector(std::size_t size)
{
    std::vector<T> result(size);

    static shino::random_int_generator<> gen(0, 100);
    gen(result.begin(), result.end());

    return result;
}

template <typename T>
void multiplication_test(const std::vector<T>& input)
{
    std::vector<T> correct_answer(input.size());

    for (std::size_t i = 0; i < input.size(); ++i)
    {
        correct_answer[i] = input[i] * 2;
    }

    std::vector<T> transformation_result(input.size()) ;

    auto multiply_by_two = [](const T& value)
    {
        return value * 2;
    };

    std::copy(input.begin(), input.end(),
              shino::transformer(multiply_by_two, transformation_result.begin()));

    if (correct_answer != transformation_result)
    {
        std::cerr << "multiplication test: answers didn't match\n";
        throw std::exception();
    }
}

template <typename T>
void stringify_test(const std::vector<T>& input)
{
    std::vector<std::string> correct_answer(input.size());

    for (std::size_t i = 0; i < input.size(); ++i)
    {
        correct_answer[i] = "The number is: " + std::to_string(input[i]);
    }

    std::vector<std::string> transformation_result(input.size());

    std::copy(input.begin(), input.end(),
              shino::transformer([](const T& value)
                                 {
                                     return "The number is: " + std::to_string(value);
                                 },
                                 transformation_result.begin()));

    if (correct_answer != transformation_result)
    {
        std::cerr << "stringify test: answers didn't match\n";
        throw std::exception();
    }
}

void run_tests()
{
    static shino::random_int_generator<std::size_t> size_gen(100, 10'000);

    constexpr std::size_t run_count = 500;
    for (std::size_t i = 0; i < run_count; ++i)
    {
        multiplication_test(generate_randomized_vector(size_gen()));
        stringify_test(generate_randomized_vector(size_gen()));
    }
}

int main()
{
    run_tests();
}

