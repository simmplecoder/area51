#ifndef CUSTOM_LIBRARY_NUMERICAL_HPP
#define CUSTOM_LIBRARY_NUMERICAL_HPP

#include <iterator>
#include <numeric>
#include <stdexcept>

namespace shino
{
    /**
     * Calculates the sum of elements of the sequence and divies by the number of elements
     * inside it. Effectively computes `std::accumulate()` divided by `std::distance()`.
     * @tparam ForwardIt A forward iterator type
     * @tparam T sum type, e.g. object of this type will hold the sum
     * @param first iterator to the first element of the sequence
     * @param last iterator to one past the end element of the sequence
     * @param initvalue initial value of the sum
     * @return average of all elements in the sequence
     */
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
