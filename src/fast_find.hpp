#ifndef FAST_FIND_HPP
#define FAST_FIND_HPP

#include <type_traits>
#include <utility>
#include <iterator>
#include "scope_exit.hpp"

namespace shino
{
    namespace impl
    {
        template <typename BidirIt, typename T>
        BidirIt find(std::true_type, BidirIt first, BidirIt last, const T& value)
        {
            if (first == last)
            {
                return last;
            }

            auto real_last = std::prev(last);
            auto copy = *real_last;
            *real_last = value;
            scope_exit { *real_last = copy; };
            auto it = first;
            for (;; ++it)
            {
                if (*it == value)
                    break;
            }

            if (it == real_last)
            {
                if (copy == value)
                {
                    return real_last;
                }
                return last;
            }

            return it;

        }

        template <typename BidirIt, typename T>
        BidirIt find(std::false_type, BidirIt first, BidirIt last, const T& value)
        {
            return std::find(first, last, value);
        }
    }


    template <typename BidirIt, typename T>
    BidirIt find(BidirIt first, BidirIt last, const T& value)
    {
        return impl::find(
                std::integral_constant<bool, std::is_nothrow_copy_assignable<std::remove_reference_t<decltype(*first)>>::value> {},
                first, last, value);
        //I'd like to allow T to be different from *first
    }
}

#endif
