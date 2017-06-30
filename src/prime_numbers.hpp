#ifndef PRIME_NUMBERS_H
#define PRIME_NUMBERS_H

#include <vector>
#include <algorithm>

namespace shino
{
    /**
     * A prime numbers container which simulates read only vector,
     * but allows resizing (by filling with more primes or cutting out right part).
     * It can provides an iterator to access the contents and other vector like
     * functionality. Also, behavior matches vector closely as well, for example
     * accessing out of range element with `operator[]` will result in
     * undefined behavior. Finds primes by trying to divide
     * @tparam NumberType an integral type that has to be big enough to accommodate
     * all of the possible values, which are produced by resizing the container.
     * It can be small for small sizes of the container.
     */
    template <typename NumberType>
    class prime_numbers
    {
        std::vector<NumberType> primes;
    public:
        using size_type = typename std::vector<NumberType>::size_type;

        /**
         * default construct prime numbers and prefills it
         */
        prime_numbers() :
                primes{2, 3, 5, 7}
        {

        }

        /**
         * @return returns the greatest prime
         */
        const NumberType& back() const
        {
            return primes.back();
        }

        /**
         * returns pointer to the internal array
         * @return
         */
        const NumberType* data() const
        {
            return primes.data();
        }

        /**
         * @return returns smallest prime, usually number 2
         */
        const NumberType& front() const
        {
            return primes.front();
        }

        /**
         * subscript operator to access element. If `index >= size()`
         * behavior is undefined.
         * @param index index of an element to access
         * @return returns the `index`th prime
         */
        const NumberType& operator[](size_type index)
        {
            return primes[index];
        }

        /**
         * accesses `index`th prime, but does resizing if the `index`
         * is bigger or equal to `size()`
         * @param index index of an element to access
         * @return returns the `index`th prime
         */
        const NumberType& at(size_type index)
        {
            if (index > primes.size() - 1)
            {
                find_n(index - primes.size() + 1);
            }

            return primes[index];
        }

        /**
         * returns const iterator (iterator which points to const elements) to
         * the first element of the underlying array
         * @return iterator to the first of the underlying array
         */
        auto begin() const
        {
            return primes.begin();
        }

        /**
         * returns const iterator (iterator which points to const elements) to
         * one past the end element of the underlying array
         * @return
         */
        auto end() const
        {
            return primes.end();
        }

        /**
         * returns const iterator (iterator which points to const elements) to
         * first element of the *reversed* array
         * @return iterator to the first element of the reversed array
         */
        auto rbegin() const
        {
            return primes.rbegin();
        }

        /**
         * returns const iterator (iterator which points to const elements) to
         * the one past the end element of the *reversed* array
         * @return iterator to the one past the end element of the reversed array
         */
        auto rend() const
        {
            return primes.rend();
        }

        /**
         * finds all primes not greater than `value`
         * @param value a value which should be greater or equal to the last element
         * of the container.
         */
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

        /**
         * finds `count` more primes
         * @param count number of primes to find in addition to existing ones
         */
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

        /**
         * @return size of the underlying array
         */
        size_type size() const
        {
            return primes.size();
        }

        /**
         * resizes the vector: if the new size is smaller, cuts off the right part, e.g.
         * the lowest primes will be preserved. IF the new size is bigger than current,
         * it will call `find_n()` with difference as parameter.
         * @param size
         */
        void resize(size_type size)
        {
            if (size < primes.size())
            {
                primes.resize(size); //user wants to shrink, no seek needed
                return;
            }

            find_n(size - primes.size());
        }

        /**
         * checks if the given number is prime. Worst case complexity of operation is \f$O(logN)\f$,
         * where \f$N\f$ is size of the container. Calls `find_until(number)` if the number exceeds
         * the last elements of the container.
         * @param number number which needs to be checked if it is prime or not.
         * @return true if the number is prime, false otherwise.
         */
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

        /**
         * Releases ownership of the underlying array. Effectively resets the container
         * to default constructed state and returns the array it held before the operation.
         * @return the internal vector before calling release
         */
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
