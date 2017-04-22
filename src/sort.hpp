#ifndef AREA51_SORT_HPP
#define AREA51_SORT_HPP

#include <functional>
#include <utility>
#include <iterator>
#include <cmath>

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
            bool sorted = true;
            for (auto j = first; j != i; ++j)
            {
                if (!cmp(*j, *std::next(j)))
                {
                    std::iter_swap(j, std::next(j));
                    sorted = false;
                }
            }
            
            if (sorted)
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
            bool sorted = true;
            for (auto j = first; j != i; ++j)
            {
                if (!cmp(*j, *std::next(j)))
                {
                    std::iter_swap(j, std::next(j));
                    sorted = false;
                }
            }
        
            if (sorted)
            {
                break;
            }
            
            sorted = true;
            // i is already dereferencable
            for (auto j = i; j != first; --j)
            {
                if (!cmp(*std::prev(j), *j))
                {
                    std::iter_swap(std::prev(j), j);
                    sorted = false;
                }
            }
            
            if (sorted)
            {
                break;
            }
        }
    }
    
    template <typename RandomAccessIt, typename Compare = std::less<>>
    void comb_sort(RandomAccessIt first, RandomAccessIt last, Compare cmp = {}, double shrink = 1.3)
    {
        auto dist = std::distance(first, last);
        if (dist < 2)
        {
            return;
        }
        
        bool sorted = true;
        for (auto i = std::prev(last); i != first; --i)
        {
            auto j0 = first;
            auto gap = std::floor(dist / shrink);
            shrink *= shrink;
            if (gap < 1)
            {
                gap = 1;
            }
            auto j1 = std::next(j0, gap);
            for (; j1 < last; ++j0, ++j1)
            {
                if (!cmp(*j0, *j1))
                {
                    std::iter_swap(j0, j1);
                    sorted = false;
                }
            }
            
            if (sorted)
            {
                break;
            }
        }
    }
}


#endif //AREA51_SORT_HPP
