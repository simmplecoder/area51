#ifndef CUSTOM_LIBRARY_TS_SCANF_HPP
#define CUSTOM_LIBRARY_TS_SCANF_HPP

#include <string>
#include <cstddef>
#include <iostream>

namespace detail
{
    template <typename InputStream, typename T>
    void read(InputStream& is, void* object)
    {
        T* real_object = reinterpret_cast<T*>(object);
        is >> *real_object;
    };
}

namespace shino {
    template<typename InputStream = std::istream, typename charT,
            typename char_traits = std::char_traits<charT>,
            typename Allocator = std::allocator<charT>,
            typename T,
            typename ... ArgTypes>
    void fmtread(InputStream &is,
                 const std::basic_string<charT, char_traits, Allocator> &format,
                 const std::basic_string<charT, char_traits, Allocator> &mark,
                 T &&object,
                 ArgTypes&& ... args) {
        auto anchor = format.find_first_of(mark);
        is >> object;
        fmtread(is, format.substr(anchor), mark, args...);
    }

    template<typename InputStream = std::istream, typename charT,
            typename char_traits = std::char_traits<charT>,
            typename Allocator = std::allocator<charT>,
            typename T>
    void fmtread(InputStream &is,
                 const std::basic_string<charT, char_traits, Allocator> &format,
                 const std::basic_string<charT, char_traits, Allocator> &mark,
                 T&& object)
    {
        is >> std::forward(object);
    };

    template<typename charT,
            typename char_traits = std::char_traits<charT>,
            typename Allocator = std::allocator<charT>,
            typename T,
            typename ... ArgTypes>
    void cfmtread(const std::basic_string<charT, char_traits, Allocator> &format,
                  T&& object, ArgTypes ... args)
    {
        fmtread(std::cin, format, std::string("{}"), std::forward<T>(object), args...);
    };
}

#endif //CUSTOM_LIBRARY_TS_SCANF_HPP
