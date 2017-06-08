#ifndef AREA51_SORT_HPP
#define AREA51_SORT_HPP

#include <functional>
#include <utility>
#include <iterator>
#include <cmath>
#include <algorithm>

namespace shino
{
    template <typename RandomAccessIt, typename Compare = std::less<>>
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

    template <typename RandomAccessIt, typename Compare = std::less_equal<>>
    void comb_sort(RandomAccessIt first, RandomAccessIt last, double shrink = 1.3, Compare cmp = {})
    {
        auto dist = std::distance(first, last);
        if (dist < 2)
        {
            return;
        }

        bool sorted = false;
        while (!sorted)
        {
            auto j0 = first;
            auto gap = std::floor(dist / shrink);
            shrink *= shrink;
            if (gap > 1)
            {
                sorted = false;
            }
            else
            {
                gap = 1;
                sorted = true;
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

    template <typename RandomAccessIt, typename Compare = std::less<>>
    void quick_sort(RandomAccessIt first, RandomAccessIt last, Compare cmp = {})
    {
        auto distance = std::distance(first, last);
        if (distance < 2)
        {
            return;
        }

        auto pivot = *std::next(first, distance / 2);

        //we need to find two sequences first ... lower_bound and
        //upper_bound ... last, where lower_bound ... upper_bound is
        //contiguous sequence of equal elements
        auto lower_bound = std::partition(first, last, [&pivot, &cmp](const auto& elem)
        {
            return cmp(elem, pivot);
        });
        auto upper_bound = std::partition(lower_bound, last, [&pivot, &cmp](const auto& elem)
        {
            return !cmp(pivot, elem);
        });

        quick_sort(first, lower_bound, cmp);
        quick_sort(upper_bound, last, cmp);
    }
}


#endif //AREA51_SORT_HPP
