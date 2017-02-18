//
// Created by olzhas on 11/11/16.
//

#ifndef CUSTOM_LIBRARY_NUMERICAL_HPP
#define CUSTOM_LIBRARY_NUMERICAL_HPP

#include <iterator>
#include <numeric>
#include <stdexcept

namespace shino
{
    template <typename ForwardIt, typename T>
    T average(ForwardIt first, ForwardIt last, T initvalue = T()) //will be 0 for builtins
    {

        for (; first != last; ++first)
        {
            initvalue += *first;
        }

        auto distance = std::distance(first, last);

        return initvalue / distance;
    };
}

#include "prime_numbers.hpp"

#endif //CUSTOM_LIBRARY_NUMERICAL_HPP
