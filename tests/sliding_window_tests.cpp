//
// Created by olzhas on 2/17/17.
//

#include "../src/sliding_window.hpp"
#include "../src/preprocessing_iterator.hpp"

#include <functional>
#include <vector>
#include <iostream>
#include <numeric>

template <typename InputIt, typename OutputIt>
void sliding_average(InputIt first, InputIt last,
                    typename std::iterator_traits<InputIt>::difference_type window_length,
                    OutputIt d_first)
{
    using value_type = typename std::iterator_traits<InputIt>::value_type;
    auto divide = [](const value_type& value)
    {
        return value / window_length;
    };

    shino::preprocessing_iterator<decltype(divide), value_type, OutputIt> iterator(divide, d_first);

    shino::sliding_window(first, last, iterator, window_length);
}

int main()
{

}