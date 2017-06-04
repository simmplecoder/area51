#ifndef AREA51_DIGIT_ITERATOR_HPP
#define AREA51_DIGIT_ITERATOR_HPP

#include <type_traits>
#include <iterator>

namespace shino
{
//input iterator that streams a number in lowest digit to highest order
//trying to go after end iterator will cause disaster!
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

        input_digit_iterator(const Integral& num) noexcept:
                number(num),
                current_digit(number % Integral(10)),
                end(false)
        {}

        input_digit_iterator() noexcept:
                end(true)
        {}

        int operator*()
        {
            return current_digit;
        }

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

        input_digit_iterator operator++(int)
        {
            auto old = *this;
            ++(*this);
            return old;
        }

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

    template <typename Integral>
    bool operator!=(const input_digit_iterator<Integral>& lhs,
                    const input_digit_iterator<Integral>& rhs)
    {
        return !(lhs == rhs);
    }
}

#endif //AREA51_DIGIT_ITERATOR_HPP
