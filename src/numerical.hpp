#ifndef CUSTOM_LIBRARY_NUMERICAL_HPP
#define CUSTOM_LIBRARY_NUMERICAL_HPP

#include <iterator>
#include <numeric>
#include <stdexcept>

namespace shino
{
    template <typename ForwardIt, typename T = typename std::iterator_traits<ForwardIt>::value_type>
    T average(ForwardIt first, ForwardIt last, T initvalue = {}) //will be 0 for builtins
    {
        auto distance = std::distance(first, last);

        auto result = std::accumulate(first, last, initvalue);

        return result / distance;
    }
}

#include "prime_numbers.hpp"

#endif //CUSTOM_LIBRARY_NUMERICAL_HPP
