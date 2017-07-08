#ifndef AREA51_ALGORITHM_HPP
#define AREA51_ALGORITHM_HPP

#include <functors.hpp>

#include <utility>
#include <map>
#include <iterator>
#include <cstddef>

namespace shino
{
    template <typename ForwardIterator, typename Comparator = std::less<>>
    std::pair<ForwardIterator, std::size_t> most_frequent(ForwardIterator first,
                                                          ForwardIterator last,
                                                          Comparator comparator = {})
    {
        auto comp = [&comparator](const auto& lhs, const auto& rhs) {
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

    template <typename CharT = char, typename Allocator>
    auto find_last_of(std::basic_string<CharT, Allocator>& s, const CharT& c)
    {
        for (auto i = s.length() - 1; i > 0; --i)
        {
            if (s[i] == c)
            {
                return i;
            }
        }

        if (s[0] == c)
        {
            return static_cast<std::size_t>(0);
        }

        return std::basic_string<CharT, Allocator>::npos;
    }

    /**
     * Fills range \f$[first, last)\f$ by repeatedly assigning
     * `initvalue` and mutating it on each element of the range.
     * Does exactly \f$last - first\f$ assignments and mutations.
     * With defaulted `mutator` effectively becomes `std::iota()`.
     * @tparam OutputIterator output iterator type
     * @tparam T value type, assignable to `*first`.
     * @tparam Functor copyable or default constructible
     * type that acts as a functor.
     * @param first iterator to the first element of the range
     * @param last iterator to one past the last element of the range
     * @param initvalue initial value of the sequence
     * @param mutator a functor which mutates `initvalue` to be
     * the next element of the desired sequence.
     */
    template <typename OutputIterator,
              typename T = typename std::iterator_traits<OutputIterator>::value_type,
              typename Functor = shino::pre_increment<>>
    void fill_by_sequence(OutputIterator first, OutputIterator last,
                           T initvalue = {}, Functor mutator = {})
    {
        while (first != last)
        {
            *first++ = initvalue;
            mutator(initvalue);
        }
    }
}
#endif //AREA51_ALGORITHM_HPP
