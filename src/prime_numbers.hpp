#ifndef PRIME_NUMBERS_H
#define PRIME_NUMBERS_H

#include <vector>
#include <algorithm>

namespace shino
{
    template <typename NumberType>
/*
    NumberType requires:
    Construction from unsigned int
    rule of three
    operator+(const NumberType&, unsgined int); or member +
    operator%(const NumberType&, const NumberType&); or member %
    Less than comparable;
    General semantic: integral positive number with enough range
*/
    class prime_numbers
    {
        std::vector<NumberType> primes;
    public:
        using size_type = typename std::vector<NumberType>::size_type;

        prime_numbers() :
                primes{2, 3, 5, 7}
        {

        }

        const NumberType& back() const
        {
            return primes.back();
        }

        const NumberType* data() const
        {
            return primes.data();
        }

        const NumberType& front() const
        {
            return primes.front();
        }

        const NumberType& operator[](size_type index)
        {
            return primes[index];
        }

        const NumberType& at(size_type index)
        {
            if (index > primes.size() - 1)
            {
                find_n(index - primes.size() + 1);
            }

            return primes[index];
        }

        auto begin() const
        {
            return primes.begin();
        }

        auto end() const
        {
            return primes.end();
        }

        auto rbegin() const
        {
            return primes.rbegin();
        }

        auto rend() const
        {
            return primes.rend();
        }

        void find_until(const NumberType& value)
        {
            for (auto i = primes.back() + 2; i <= value; i += 2)
            {
                if (is_prime(i))
                {
                    primes.push_back(i);
                }
            }
        }

        void find_n(size_type count = 1)
        {
            size_type needed = primes.size() + count;

            for (auto i = primes.back() + 2; primes.size() < needed; i += 2)
            {
                if (is_prime(i))
                {
                    primes.push_back(i);
                }
            }
        }

        size_type size() const
        {
            return primes.size();
        }

        void resize(size_type size)
        {
            if (size < primes.size())
            {
                primes.resize(size); //user wants to shrink, no seek needed
                return;
            }

            find_n(size - primes.size());
        }

        bool prime(const NumberType& number)
        {
            if (!(number < primes.back()))
                // < is usually implemented first
            {
                find_until(number);
            }

            //primes are strictly in ascending order
            return std::binary_search(primes.begin(), primes.end(), number);
        }

        std::vector<NumberType> release()
        {
            std::vector<NumberType> old{2, 3, 5, 7};
            old.swap(primes);
            return old;
        }

    private:
        bool is_prime(const NumberType& number)
        {
            for (const auto& prime : primes)
            {
                if (number / prime < prime)
                {
                    return true;
                }

                if (number % prime == 0)
                {
                    return false;
                }
            }

            return true;
        }
    };
}

#endif //CUSTOM_LIBRARY_PRIME_NUMBERS_HPP
