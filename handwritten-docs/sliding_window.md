#sliding_window<>()

The function implements generic sliding window with linear time complexity.

>Window: given container `container` with size `size`, and desired 
window length `length` and starting point `i`,  a window is a result of user supplied
function on elements `container[i]` through `container[i + length - 1]`. For example,
`std::accumulate<>()` computes a window with `length` equal to `size`.

>Sliding window: given container `container` with size `size`, window length `length`,
computes `size - length + 1` *window*s, which are formed by applying user supplied 
operation to add elements into window and remove elements from it. Each window is
formed by removing first element in the previous window and adding the next element after
the previous window.
###Specification:

>Given `InputIterator first, last` (which conform `InputIterator` concept), 
`OutputIterator d_first` (which conform `OutputIterator` concept), 
`window_length`, `init`, `BinaryAddOp add_op`, `BinaryRemoveOp remove_op` computes
 *sliding window* of range denoted by `[first, last)` starting with initial 
 window `init`, and writes result into range denoted by `d_first`, applying `add_op`
 to add elements into the window, and `remove_op` to remove elements from the window.
 
##Usage:

The algorithm is meant to be used with `transform_iterator` to reach full potential.
Any grouping operations are best performed by sliding window. For example, sliding average:


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

It is recommended to writ more specialized algorithms on top of sliding window, to
facilitate clarity and reduce error vectors.
