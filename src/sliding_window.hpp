#ifndef SUNRISE_SLIDING_WINDOW_HPP
#define SUNRISE_SLIDING_WINDOW_HPP

#include <functional>
#include <stdexcept>
#include <iterator>

namespace shino
{
    template <typename BidirIt,
              typename OutputIt,
              typename T = typename std::iterator_traits<BidirIt>::value_type,
              typename BinaryAddOp = std::plus<>,
              typename BinaryRemoveOp = std::minus<>>
    std::pair<BidirIt, OutputIt> sliding_window(BidirIt first,
                                                BidirIt last,
                                                OutputIt d_first,
                                                typename std::iterator_traits<BidirIt>::difference_type length,
                                                T init = {},
                                                BinaryAddOp add_op = {},
                                                BinaryRemoveOp remove_op = {})
    {
        if (first == last || length == 0)
        {
            return std::make_pair(first, d_first);
        }

        BidirIt milestone(std::next(first, length));
        auto tail = first;

        while (first != last && first != milestone)
        {
            init = add_op(init, *first);
            ++first;
        }

        if (first != milestone)
        {
            throw std::invalid_argument("Iterator range is smaller than length of the window");
        }

        *d_first = init;
        ++d_first;

        if (first == last)
        {
            return std::make_pair(first, d_first);
        }

        while (first != last)
        {
            init = remove_op(init, *tail);
            init = add_op(init, *first);
            *d_first = init;
            ++tail;
            ++first;
            ++d_first;
        }

        return std::make_pair(first, d_first);
    }
}

#endif //SUNRISE_SLIDING_WINDOW_HPP
