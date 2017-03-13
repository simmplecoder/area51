#ifndef AREA51_ALGORITHM_HPP
#define AREA51_ALGORITHM_HPP

#include <utility>
#include <map>
#include <iterator>
#include <cstddef>

template <typename ForwardIterator, typename Comparator = std::less<>>
std::pair<ForwardIterator, std::size_t> most_frequent(ForwardIterator first,
                                                      ForwardIterator last,
                                                      Comparator comparator = {})
{
    auto comp = [&comparator](const auto& lhs, const auto& rhs)
    {
        return comparator(lhs.get(), rhs.get());
    };

    std::map<std::reference_wrapper<typename std::iterator_traits<ForwardIterator>::value_type>,
            std::size_t, decltype(comp)> counts(comp);

    std::size_t frequency = 0;
    auto most_freq = first;
    while (first != last)
    {
        std::size_t current = ++counts[*first];
        if (current > frequency)
        {
            frequency = current;
            most_freq = first;
        }

        ++first;
    }

    return std::make_pair(most_freq, frequency);
}

//template <typename ForwardIterator>
//std::pair<ForwardIterator, std::size_t> most_frequent(ForwardIterator first, ForwardIterator last)
//{
//    return most_frequent(first, last, std::less<>{});
//}

#endif //AREA51_ALGORITHM_HPP
