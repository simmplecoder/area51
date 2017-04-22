#ifndef AREA51_SORT_HPP
#define AREA51_SORT_HPP

#include <functional>
#include <utility>
#include <iterator>

namespace shino
{
    template<typename RandomAccessIt, typename Compare = std::less<>>
    void bubble_sort(RandomAccessIt first, RandomAccessIt last, Compare cmp = {})
    {
        if (std::distance(first, last) < 2)
        {
            return;
        }
        
        for (auto i = std::prev(last); i != first; --i)
        {
            bool swapped = false;
            for (auto j = first; j != i; ++j)
            {
                if (!cmp(*j, *std::next(j)))
                {
                    std::iter_swap(j, std::next(j));
                    swapped = true;
                }
            }
            
            if (!swapped)
            {
                break;
            }
        }
    }
    
    template <typename RandomAccessIt, typename Compare = std::less<>>
    void insertion_sort(RandomAccessIt first, RandomAccessIt last, Compare cmp = {})
    {
        if (std::distance(first, last) < 2)
        {
            return;
        }
        
        for (auto i = std::next(first); i != last; ++i)
        {
            auto j = i;
            while (std::prev(j) != first && !cmp(*std::prev(j), *j))
            {
                std::iter_swap(std::prev(j), j);
                --j;
            }
        }
    }
    
    template <typename RandomAccessIt, typename Compare = std::less<>>
    void selection_sort(RandomAccessIt first, RandomAccessIt last, Compare cmp = {})
    {
        if (std::distance(first, last) < 2)
        {
            return;
        }
        
        for (auto i = first; i != last; ++i)
        {
            for (auto j = std::next(i); j != last; ++j)
            {
                if (!cmp(*i, *j))
                {
                    std::iter_swap(i, j);
                }
            }
        }
    }
    
    template <typename RandomAccessIt, typename Compare = std::less<>>
    void shaker_sort(RandomAccessIt first, RandomAccessIt last, Compare cmp = {})
    {
        if (std::distance(first, last) < 2)
        {
            return;
        }
    
        for (auto i = std::prev(last); i != first; --i)
        {
            bool swapped = false;
            for (auto j = first; j != i; ++j)
            {
                if (!cmp(*j, *std::next(j)))
                {
                    std::iter_swap(j, std::next(j));
                    swapped = true;
                }
            }
        
            if (!swapped)
            {
                break;
            }
            
            swapped = false;
            
            // i is already dereferencable
            for (auto j = i; j != first; --j)
            {
                if (!cmp(*std::prev(j), *j))
                {
                    std::iter_swap(std::prev(j), j);
                    swapped = true;
                }
            }
            
            if (!swapped)
            {
                break;
            }
        }
    }
    
    
}


#endif //AREA51_SORT_HPP
