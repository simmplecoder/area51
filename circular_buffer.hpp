//
// Created by olzhas on 11/11/16.
//

#ifndef CUSTOM_LIBRARY_CIRCULAR_BUFFER_HPP
#define CUSTOM_LIBRARY_CIRCULAR_BUFFER_HPP

#include <cstddef>
#include <utility>
#include <new>


//TODO: MAKE THIS TO BE GREAT!
namespace shino {
    template<typename T, std::size_t mcapacity>
    class circular_buffer {
        T *data;
        T *begin;
        T *end;
        std::size_t msize;
        bool is_empty;

        template<bool trivially_destructible>
        struct destructor {
            void destroy(T *object) {
                object->~T();
            }

            void destroy_n(T *objects, std::size_t sz) {
                for (std::size_t i = 0; i < sz; ++i) {
                    objects->~T();
                    ++objects;
                }

                ::operator delete(objects);
            }
        };

        template<>
        struct destructor<true> {
            void destroy(T *object) {
                //empty, since trivially destroyable
            }

            void destroy_n(T *objects, std::size_t sz) {
                ::operator delete(objects);
            }
        };

        destructor<std::is_trivially_destructible<T>::value> destroyer;

    public:
        using container = circular_buffer<T, mcapacity>;
        using value_type = T;
        using reference = value_type &;
        using pointer = T *;
        using const_reference = const reference;
        using size_type = std::size_t;

        circular_buffer() :
                data((pointer) ::operator new(sizeof(value_type) * mcapacity)),
                msize(0),
                begin(data),
                end(data) {}

        template<typename ... ArgTypes>
        void emplace(ArgTypes ... args) {
            end = new(end) T(args...);
            ++end;
            if (end == data + mcapacity) {
                end = data;
            }

            if (msize != mcapacity) {
                ++msize;
            }
        }

        void push(const T &value) {
            end = new(end) T(value);
            ++end;
            if (end == data + mcapacity) {
                end = data;
            }

            if (msize != mcapacity) {
                ++msize;
            }
        }

        void push(T &&value) {
            end->T(value);
            ++end;
            if (end == data + mcapacity) {
                end = data;
            }

            if (msize != mcapacity) {
                ++msize;
            }
        }

        const_reference front() {
            return *begin;
        }

        void pop() {
            destroyer.destroy(begin);
            ++begin;
            if (begin == data + mcapacity) {
                begin = data;
            }

            if (msize != 0) {
                --msize;
            }
        }

        size_type size() {
            return msize;
        }

        constexpr size_type capacity() {
            return mcapacity;
        }

        bool full() {
            return msize == mcapacity;
        }

        bool empty() {
            return msize == 0;
        }

        ~circular_buffer() {
            destroyer.destroy_n(data, mcapacity);
        }
    };
}
#endif //CUSTOM_LIBRARY_CIRCULAR_BUFFER_HPP
