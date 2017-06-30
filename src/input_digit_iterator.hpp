#ifndef AREA51_DIGIT_ITERATOR_HPP
#define AREA51_DIGIT_ITERATOR_HPP

#include <type_traits>
#include <iterator>

namespace shino
{
    /**
     * A class that returns the digit of the provided number on each dereference from lowest significant to most.
     * Incrementing will divide the number by ten and cache current digit. The default constructed iterator
     * is treated as end iterator. Providing zero as integer will make iterator return zero once and become
     * an end iterator.
     * @tparam Integral an integer type digits of which to stream
     */
    template <typename Integral = int>
    class input_digit_iterator
    {
        Integral number;
        Integral current_digit;
        bool end;
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = int;
        using difference_type = std::size_t;
        using pointer = int*;
        using reference = int&;

        /**
         * Constructor to initialize iterator with a number.
         * Will use the number to provide its digits, even if integer zero is provided.
         * @param num a number whose digits need to be streamed
         */
        input_digit_iterator(const Integral& num) noexcept:
                number(num),
                current_digit(number % Integral(10)),
                end(false)
        {}

        /**
         * Creates end iterator, e.g. one past the end, non dereferencable iterator
         */
        input_digit_iterator() noexcept:
                end(true)
        {}

        /**
         * @return returns current digit
         */
        int operator*()
        {
            return current_digit;
        }

        /**
         * Advances iterator by dividing the number by ten and caching the digit of the remained number.
         * @return reference to advanced iterator, e.g. *this
         */
        input_digit_iterator& operator++()
        {
            //do not divide until checked if end
            //because then it will output 0 twice
            if (number < Integral(10))
            {
                end = true;
                return *this;
            }

            number /= Integral(10);
            current_digit = number % Integral(10);
            return *this;
        }

        /**
         * the same as prefix increment, except it returns a copy of the iterator before incrementing.
         * @return iterator before incrementing
         */
        input_digit_iterator operator++(int)
        {
            auto old = *this;
            ++(*this);
            return old;
        }

        /**
         * comparison operator, very inefficient to compare two non-end iterators, but is efficient
         * to compare one non-end and one end iterator
         * @param lhs left hand-side iterator to compare
         * @param rhs right hand-side iterator to compare
         * @return true if they are equal (both are end iterators or both have exactly
         * the same state), false otherwise.
         */
        friend bool operator==(const input_digit_iterator<Integral>& lhs,
                               const input_digit_iterator<Integral>& rhs)
        {
            if (lhs.end && rhs.end)
            {
                return true;
            }

            return lhs.end == rhs.end && //check first, since more frequent
                   lhs.number == rhs.number &&
                   lhs.current_digit == rhs.current_digit;
        }
    };

    /**
     * Negates the result of equality operator
     * @tparam Integral an integer type used in `input_digit_iterator`s
     * @param lhs left hand-side iterator to compare
     * @param rhs right hand-side iterator to compare
     * @return negation of the equality
     * @return negation of the equality
     */
    template <typename Integral>
    bool operator!=(const input_digit_iterator<Integral>& lhs,
                    const input_digit_iterator<Integral>& rhs)
    {
        return !(lhs == rhs);
    }
}

#endif //AREA51_DIGIT_ITERATOR_HPP
