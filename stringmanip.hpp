//
// Created by olzhas on 11/10/16.
//

#ifndef CUSTOM_LIBRARY_STRINGMANIP_HPP
#define CUSTOM_LIBRARY_STRINGMANIP_HPP

#include <iterator>
#include <sstream>
#include <string>

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
}

#endif //CUSTOM_LIBRARY_STRINGMANIP_HPP
