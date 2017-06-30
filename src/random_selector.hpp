#ifndef AREA51_RANDOM_SELECTOR_HPP
#define AREA51_RANDOM_SELECTOR_HPP

#include "random_int_generator.hpp"
#include "utilities.hpp"

#include <vector>
#include <utility>
#include <iterator>
#include <stdexcept>

/**
 * Takes ownership of provided pool of elements, and allow randomly
 * selecting one when asked to. Uses non standard RandomNumberGenerator,
 * see `shino::random_int_generator`.
 * @tparam T element type of a pool.
 * @tparam RandomNumberGenerator an rng which will generate
 * index of the element to be selected next.
 */
template <typename T,
          typename RandomNumberGenerator = shino::random_int_generator<std::size_t>>
class random_selector
{
    std::vector<T> pool;
    RandomNumberGenerator rng;
public:
    using value_type = std::add_const_t<T>;
    using reference = value_type&;
    using iterator = typename std::vector<T>::const_iterator;

    /**
     * Initializes pool of elements by elements of the provided sequence.
     * Constructing the class with empty sequence is ok, but accessing it
     * will invoke undefined behavior.
     * @tparam InputIt input iterator type
     * @param first iterator the first element of the sequence
     * @param last iterator to the one past the last element of the sequence
     */
    template <typename InputIt>
    random_selector(InputIt first, InputIt last):
            pool(first, last),
            rng(0, pool.size() - 1)
    {
        if (pool.size() == 0)
        {
            throw std::invalid_argument("Range cannot be empty");
        }
    }

    /**
     * Initializes pool from `std::initializer_list`. This constructor
     * is not guaranteed to call iterator based constructor, thus
     * no additional assumptions should be made.
     * @param init_list an initialier_list to use to initialize pool
     */
    random_selector(std::initializer_list<T> init_list) :
            pool(init_list),
            rng(0, init_list.size() - 1)
    {
        if (pool.size() == 0)
        {
            throw std::invalid_argument("Range cannot be empty");
        }
    }

    //let T and RandomNumberGenerator decide on rule of 5

    /**
     * @return a reference to the randomly selected element. Do note that reference refers to
     * const value, e.g. `const T&`.
     */
    reference operator()()
    {
        return pool[rng()];
    }

    /**
     * For each element in the `[first, last)` randomly selects one element and writes it.
     * @tparam OutputIt output iterator type
     * @param first iterator to the first element of the destination sequence
     * @param last iterator to the one past the last element of the destination sequence
     */
    template <typename OutputIt>
    void operator()(OutputIt first, OutputIt last)
    {
        while (first != last)
        {
            *first++ = pool[rng()];
        }
    }

    /**
     * Resets the current random number generator with provided one.
     * @tparam QRandomNumberGenerator qualified type of the `RandomNumberGenerator`
     * provided earlier
     * @param next_rng state of the rng to set the current to.
     */
    template <typename QRandomNumberGenerator,
              typename = shino::enable_sfinae<QRandomNumberGenerator,
                      RandomNumberGenerator>>
    void reset_generator(QRandomNumberGenerator&& next_rng)
    {
        rng = next_rng;
    }

    /**
     * @return number of elements in the pool
     */
    std::size_t data_size()
    {
        return pool.size();
    }

    /**
     * @return iterator to the first element of the underlying pool. The returned iterator
     * points to `const` elements.
     */
    iterator begin()
    {
        return pool.cbegin();
    }

    /**
     * @return one past the end iterator of the underlying pool. The returned iterator points to
     * `const` elements.
     */
    iterator end()
    {
        return pool.cend();
    }
};

#endif //AREA51_RANDOM_SELECTOR_HPP
