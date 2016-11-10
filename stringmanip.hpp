//
// Created by olzhas on 11/10/16.
//

#ifndef CUSTOM_LIBRARY_STRINGMANIP_HPP
#define CUSTOM_LIBRARY_STRINGMANIP_HPP

#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace shino {
    template<typename InputIt, typename Separator = std::string, typename Concluder = std::string>
    std::string join(InputIt first,
                     InputIt last,
                     const Separator &separator,
                     const Concluder &concluder) {
        if (first == last) {
            return concluder;
        }

        std::stringstream ss;
        ss << *first;
        ++first;

        while (first != last) {
            ss << separator;
            ss << *first;
            ++first;
        }

        ss << concluder;

        return ss.str();
    }

    template <typename charT, typename char_traits = std::char_traits<charT>, typename RandomAccesIt>
    void z_function(const std::basic_string<charT, char_traits>& str, RandomAccesIt z)
    {
        std::size_t l = 0;
        std::size_t r = 0;
        std::size_t len = str.length();
        for (std::basic_string<charT, char_traits>::size_type i = 0;
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

    template <typename charT, typename char_traits = std::char_traits<charT>>
    std::vector<std::size_t> z_function(const std::basic_string<charT, char_traits>& str)
    {
        std::size_t len = str.length();
        std::vector<std::size_t> z (len);
        for (int i=1, l=0, r=0; i<len; ++i) {
            if (i <= r) {
                z[i] = std::min(r - i + 1, z[i - l]);
            }
            while (i+z[i] < len && str[z[i]] == str[i+z[i]])
                ++z[i];
            if (i+z[i]-1 > r)
                l = i,  r = i+z[i]-1;
            }
            return z;
    };
}



#endif //CUSTOM_LIBRARY_STRINGMANIP_HPP