//
// Created by olzhas on 11/11/16.
//

#ifndef CUSTOM_LIBRARY_CIRCULAR_BUFFER_HPP
#define CUSTOM_LIBRARY_CIRCULAR_BUFFER_HPP

#include <cstddef>
#include <utility>
#include <new>
#include <vector>


//TODO: MAKE THIS TO BE GREAT!
namespace shino {
    template <typename T, template <typename ... > typename container = std::vector<T>>
    class circular_buffer
    {
        container cont;
    public:

    };
}
#endif //CUSTOM_LIBRARY_CIRCULAR_BUFFER_HPP
