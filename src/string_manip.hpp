#ifndef CUSTOM_LIBRARY_STRINGMANIP_HPP
#define CUSTOM_LIBRARY_STRINGMANIP_HPP

#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include "iterator.hpp"

namespace shino
{
    /**
     * Joins the string, putting separator in between
     * elements and adding concluder at the end
     * @tparam InputIt input iterator type for strings to be joined
     * @tparam Separator separator type to put in between strings
     * @tparam Concluder concluder type to put at the end
     * @param first iterator to the first string to be joined
     * @param last one past the end iterator of strings to be joined
     * @param separator a separator to put in between elements
     * @param concluder a concluder to put at the end
     * @return an std::string with result of joining
     */
    template <typename InputIt, typename Separator = std::string, typename Concluder = std::string>
    std::string join(InputIt first, InputIt last,
                     const Separator& separator,
                     const Concluder& concluder)
    {
        if (first == last)
        {
            return concluder;
        }

        std::stringstream ss;
        ss << *first;
        ++first;

        while (first != last)
        {
            ss << separator;
            ss << *first;
            ++first;
        }

        ss << concluder;

        return ss.str();
    }

    /**
     * an algorithm that writes lengths of substrings starting from
     * index i.
     * See https://en.wikipedia.org/wiki/String_searching_algorithm for more.
     * Behaves the same like version returning vector, except it writes output
     * into provided iterator z
     * @tparam charT character type
     * @tparam char_traits a traits class that define operations on charT
     * @tparam RandomAccesIt
     * @param str the string to process
     * @param z output iterator to which write the result
     */
    template <typename charT, typename char_traits = std::char_traits<charT>, typename RandomAccesIt>
    void z_function(const std::basic_string<charT, char_traits>& str, RandomAccesIt z)
    {
        std::size_t l = 0;
        std::size_t r = 0;
        std::size_t len = str.length();
        for (typename std::basic_string<charT, char_traits>::size_type i = 0;
             i < str.length(); ++i)
        {
            if (i <= r)
            {
                z[i] = std::min(r - i + 1, z[i - l]);
            }
            while (i + z[i] < len && str[z[i]] == str[i + z[i]])
            {
                ++z[i];
            }

            if (i + z[i] - 1 > r)
            {
                l = i;
                r = i + z[i] - 1;
            }
        }
    };

    /**
     * an algorithm that writes lengths of substrings starting from
     * index i.
     * See https://en.wikipedia.org/wiki/String_searching_algorithm for more.
     * Behaves the same like version with iterator, except it returns a vector
     * instead of providing a chance to supply iterator.
     * @tparam charT
     * @tparam char_traits
     * @param str string to process
     * @return a vector with result of the z-function
     */
    template <typename charT, typename char_traits = std::char_traits<charT>>
    std::vector<std::size_t> z_function(const std::basic_string<charT, char_traits>& str)
    {
        std::size_t l = 0;
        std::size_t r = 0;
        std::size_t len = str.length();
        std::vector<std::size_t> z(len);
        for (int i = 1; i < len; ++i)
        {
            if (i <= r)
            {
                z[i] = std::min(r - i + 1, z[i - l]);
            }
            while (i + z[i] < len && str[z[i]] == str[i + z[i]])
                ++z[i];
            if (i + z[i] - 1 > r)
                l = i, r = i + z[i] - 1;
        }
        return z;
    }

    /**
     * Concatenate string with itself \f$n-1\f$ times.
     * `in * 0` will return empty string. Uses binary concatenation,
     * in a sense that operation is roughly \f$O(logN)\f$ complexity.
     * @tparam charT string element type
     * @tparam char_traits traits that define operations on charT
     * @tparam Allocator allocator which string type uses for allocations
     * @param in string to use in concatenations
     * @param n times to concatenate - 1
     * @return result of concatenations
     */
    template <typename charT, typename char_traits = std::char_traits<charT>, class Allocator = std::allocator<charT>>
    std::basic_string<charT, char_traits, Allocator>
    operator*(const std::basic_string<charT, char_traits, Allocator>& in, std::size_t n)
    {
        if (n == 0)
            return {};
        if (n == 1)
            return in;

        std::string result;
        if (n % 2 == 0)
        {
            auto half = in * (n / 2);
            return half + half;
        }
        else
        {
            return (in * (n - 1)) + in;
        }
    }

    /**
     * Behaves in the same as its reversed version.
     * @tparam charT string element type
     * @tparam char_traits traits that define operations on charT
     * @tparam Allocator allocator which string type uses for allocations
     * @param n times to concatenate - 1
     * @param in string to use in concatenations
     * @return result of concatenations
     */
    template <typename charT, typename char_traits = std::char_traits<charT>, class Allocator = std::allocator<charT>>
    std::basic_string<charT, char_traits, Allocator>
    operator*(std::size_t n, const std::basic_string<charT, char_traits, Allocator>& in)
    {
        return in * n;
    }
}


#endif //CUSTOM_LIBRARY_STRINGMANIP_HPP
