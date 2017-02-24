//
// Created by olzhas on 2/17/17.
//

#include "../src/sliding_window.hpp"
#include "../src/transform_iterator.hpp"

#include <vector>
#include <iostream>
#include <utility>

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

    auto iterator = shino::transformer(divide, d_first); //transform_iterator<Functor, Iterator>

    auto result = shino::sliding_window(first, last, iterator, window_length);

    return std::make_pair(result.first, result.second.internal_iterator());
}

int main()
{
    constexpr int element_value = 2;
    constexpr std::size_t size = 8;
    constexpr std::size_t window_length = 4;
    std::vector<int> v(size, element_value);
    std::vector<double> output(size - window_length + 1);

    sliding_average(v.begin(), v.end(), window_length, output.begin());

    std::cout << "result: ";
    for (const auto& elem: output)
    {
        std::cout << elem << ' ';
    }
}