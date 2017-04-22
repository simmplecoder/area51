#ifndef AREA51_RANDOM_SELECTOR_HPP
#define AREA51_RANDOM_SELECTOR_HPP

#include "random_int_generator.hpp"
#include "utilities.hpp"

#include <vector>
#include <utility>
#include <iterator>
#include <stdexcept>

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
    
    random_selector(std::initializer_list<T> init_list):
            pool(init_list),
            rng(0, init_list.size() - 1)
    {
        if (pool.size() == 0)
        {
            throw std::invalid_argument("Range cannot be empty");
        }
    }
    
    //let T and RandomNumberGenerator decide on rule of 5
    
    reference operator()()
    {
        return pool[rng()];
    }
    
    template <typename OutputIt>
    void operator()(OutputIt first, OutputIt last)
    {
        while (first != last)
        {
            *first++ = pool[rng()];
        }
    }
    
    //sfinae friendly reset
    //Q stands for Qualified
    template <typename QRandomNumberGenerator,
            typename = shino::enable_sfinae<QRandomNumberGenerator,
                    RandomNumberGenerator>>
    void reset_generator(QRandomNumberGenerator&& next_rng)
    {
        rng = next_rng;
    }
    
    std::size_t data_size()
    {
        return pool.size();
    }
    
    iterator begin()
    {
        return pool.cbegin();
    }
    
    iterator end()
    {
        return pool.cend();
    }
};

#endif //AREA51_RANDOM_SELECTOR_HPP
