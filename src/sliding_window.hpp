//
// Created by olzhas on 2/17/17.
//

#ifndef SUNRISE_SLIDING_WINDOW_HPP
#define SUNRISE_SLIDING_WINDOW_HPP

#include <functional>
#include <stdexcept>
#include <iterator>

/**
 * @namespace shino
 * @brief everything in the library is put into this namespace
 *
 * The namespace serves to house all of the functions, classes
 * found in this library.
 */
namespace shino
{
    /**
    * \fn sliding_window
    * \brief sliding window that writes the results into d_first
    * @param first - beginning of the input range
    * @param last - end of the input range
    * @param d_first - beginning of the output range
    * @param length - length of the sliding window
    * @param init - initial value for the sliding window. It will be used to create the window
    * @param op - function object that adds element into the window
    * @param undo - function object that removes elements from the window
    *
    * The function implements linear time sliding window. It starts off from the first element
    * in the given range and slowly adds them to the list to create window.
    * It uses `op` to add elements into the window. For example `std::plus<>`
    * could be used to add an element into the window. Throughout the range, algorithm
    * will keep removing elements from the back using `undo` and adding elements to the front
    * using `op`. Every time window is created or modified the current state is written into
    * range denoted by `d_first`.
    */
    template<typename BidirIt,
             typename OutputIt,
             typename T = typename std::iterator_traits<BidirIt>::value_type,
             typename BinaryDoOp = std::plus<>,
             typename BinaryUndoOp = std::minus<>>
    void sliding_window(BidirIt first,
                        BidirIt last,
                        OutputIt d_first,
                        typename std::iterator_traits<BidirIt>::difference_type length,
                        T init = {},
                        BinaryDoOp op = {},
                        BinaryUndoOp undo = {})
    {
        if (first == last || length == 0)
        {
            return;
        }

        typename std::iterator_traits<BidirIt>::difference_type counter{}; //try to default construct
        auto tail = first;

        while (counter < length && first != last)
        {
            init = op(init, *first);
            ++first;
            ++counter;
        }

        if (counter != length)
        {
            throw std::invalid_argument("Iterator range is smaller than length of the window");
        }
        *d_first = init;
        ++d_first;

        if (first == last)
        {
            return;
        }

        while (first != last)
        {
            init = undo(init, *tail);
            init = op(init, *first);
            *d_first = init;
            ++tail;
            ++first;
            ++d_first;
        }
    }
}

#endif //SUNRISE_SLIDING_WINDOW_HPP
