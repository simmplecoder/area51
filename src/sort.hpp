/**
 * @file the file includes all sorting algorithms provided in the library.
 * All comparisons to establish ordering are performed through comparison object,
 * which should strictly follow [compare concept](http://en.cppreference.com/w/cpp/concept/Compare).
 * There is an exception for comb sort, which uses, equals_less,
 * since it is not possible to implement it otherwise.
 */

#ifndef AREA51_SORT_HPP
#define AREA51_SORT_HPP

#include <functional>
#include <utility>
#include <iterator>
#include <cmath>
#include <algorithm>

namespace shino
{
    /**
     * Sorting algorithm.
     * Repetitively compares adjacent elements, swapping if predicate returns false,
     * bringing largest values to the end.
     * Shrinks sorting range on each iterations.
     * @tparam RandomAccessIt random access iterator type
     * @tparam Compare a comparison type
     * @param first first element of the range
     * @param last one past the end element of the range
     * @param cmp comparison object that checks for strict weak ordering
     */
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

    /**
     * Sorting algorithm.
     * On each iterations puts the current element into its position on the
     * left hand side of the sequence, thus increasing sorted sequence in size on each iteration.
     * @tparam RandomAccessIt random access iterator type
     * @tparam Compare a comparison type
     * @param first first element of the range
     * @param last one past the end element of the range
     * @param cmp comparison object that checks for strict weak ordering
     */
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

    /**
     * Sorting algorithm.
     * On each iteration finds the smallest element and puts it to the leftmost side,
     * thus on each iteration increasing sorted sequence in size.
     * @tparam RandomAccessIt random access iterator type
     * @tparam Compare a comparison type
     * @param first first element of the range
     * @param last one past the end element of the range
     * @param cmp comparison object that checks for strict weak ordering
     */
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

    /**
     * Sorting algorithm.
     * Repetitively compares adjacent elements, swapping if the predicate returns false,
     * bringing one greatest element to the right side
     * of the sequence, and does another run to bring the smallest element to the bottom.
     * Differs from bubble sort in doing that extra run down, though still sorted range is
     * on the right.
     * @tparam RandomAccessIt random access iterator type
     * @tparam Compare a comparison type
     * @param first first element of the range
     * @param last one past the end element of the range
     * @param cmp comparison object that checks for strict weak ordering
     */
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

    /**
     * Sorting algorithm.
     * Repetitively compares elements that are possibly far away from each other, swapping them
     * if the predicate returns false,bringing the largest grabbed value to the right. On each iteration the gap between
     * compared elements shrink, thus boiling down to bubble sort at the end. The shrinking
     * depends on the shrink factor and the size of the sequence, thus comparison gap is
     * \f$size / shrinkfactor^i\f$, where \f$i\f$ is the current iteration. Eventually the
     * gap reaches 1, which means that it will compare adjacent elements, and the gap size
     * never gets below that.
     * @tparam RandomAccessIt random access iterator type
     * @tparam Compare a comparison type
     * @param first first element of the range
     * @param last one past the end element of the range
     * @param shrink a speed on which the gap between compared elements decreases
     * @param cmp comparison object that checks for strict weak ordering
     */
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

    /**
     * Famous sorting algorithm.
     * Repetitively [partitions](https://en.wikipedia.org/wiki/Partition_problem) elements
     * of the range, dividing it into three parts: first one is elements smaller than the current
     * pivot, the range that is equal to pivot, and range which has elements with values higher
     * than the current pivot. The current pivot is the middle element of the range before the
     * operations. On each iterations recurs into the left side and right side.
     * @tparam RandomAccessIt random access iterator type
     * @tparam Compare a comparison type
     * @param first first element of the range
     * @param last one past the end element of the range
     * @param cmp comparison object that checks for strict weak ordering
     */
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
