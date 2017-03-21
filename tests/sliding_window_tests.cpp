//
// Created by olzhas on 2/17/17.
//

#include "../src/sliding_window.hpp"
#include "../src/transform_iterator.hpp"
#include "../src/random_engine.hpp"
#include "../src/numerical.hpp"

#include <vector>
#include <iostream>
#include <utility>
#include <cassert>

constexpr std::size_t test_count = 500;

template <typename InputIt, typename OutputIt>
std::pair<InputIt, OutputIt> sliding_average(InputIt first, InputIt last,
                    const typename std::iterator_traits<InputIt>::difference_type window_length,
                    OutputIt d_first)
{
    using value_type = typename std::iterator_traits<InputIt>::value_type;
    auto divide = [&window_length](const value_type& value)
    {
        return value / window_length;
    };

    auto iterator = shino::transformer(divide, d_first);

    auto result = shino::sliding_window(first, last, iterator, window_length);

    return std::make_pair(result.first, result.second.internal_iterator());
}

template <typename T>
std::vector<T> slow_sliding_average(const std::vector<T>& input, std::size_t window_length)
{
    auto head = std::next(input.begin(), window_length);
    auto tail = input.begin();

    std::vector<T> output(input.size() - window_length + 1);
    auto d_first = output.begin();

    while (head != input.end())
    {
        *d_first++ = shino::average(tail++, head++);
    }
    *d_first = shino::average(tail, head);

    return output;
}

template <typename T = int>
std::vector<T> generate_vector(std::size_t size)
{
    std::vector<T> v(size);

    static shino::random_int_generator<> gen;
    gen(v.begin(), v.end());

    return v;
}

void sliding_average_test(std::size_t size, std::size_t window_length)
{
    if (size >= window_length)
    {
        std::cerr << "Generator is working incorrectly: "
                "window length matches or exceeds "
                "size of the vector";
    }
    auto input = generate_vector(size);

    auto slow_sliding_average_result = slow_sliding_average(input, window_length);

    std::vector<int> sliding_average_result(input.size() - window_length + 1);
    sliding_average(input.begin(), input.end(), window_length, sliding_average_result.begin());

    if (sliding_average_result == slow_sliding_average_result)
    {
        
    }
}

void run_tests()
{
    shino::random_int_generator<std::size_t> size_gen(100, 10'000);
    shino::random_int_generator<std::size_t> window_length_gen(1, 10);

    for (std::size_t i = 0; i < test_count; ++i)
    {
        sliding_average_test(size_gen(), window_length_gen());
    }
}

int main()
{
    run_tests();
}