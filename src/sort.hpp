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
                    swapped = true;
                    std::iter_swap(j, std::next(j));
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
