//
// Created by olzhas on 11/12/16.
//

#ifndef CUSTOM_LIBRARY_ITERATOR_HPP
#define CUSTOM_LIBRARY_ITERATOR_HPP

#include <iterator>

namespace shino {
    template<typename T>
    class stumbled_iterator : public std::iterator<std::input_iterator_tag, T>
    {
        const T &reference;
    public:
        using iterator_category = std::input_iterator_tag;
        stumbled_iterator(const T &reference_) :
                reference(reference_) {}

        constexpr stumbled_iterator &operator++() {
            return *this;
        }

        constexpr stumbled_iterator operator++(int) {
            return *this;
        }

        const T &operator*() {
            return reference;
        }
    };

    template <typename Container, typename T = typename Container::value_type>
    class append_iterator : public std::iterator<std::output_iterator_tag, typename Container::value_type>
    {
        Container& container;
    public:
        class proxy
        {
            Container& container;
            friend class append_iterator<Container, T>;
        public:
            proxy& operator=(const T& value)
            {
                container += value;
            }

            proxy(const proxy& other) = default;
            proxy& operator=(const proxy& other) = delete;

            proxy(proxy&& other) = default;
            proxy& operator=(proxy&& other) = delete;

        private:
            proxy(); //prevent construction from outside
            proxy(Container& ref):
                    container(ref)
            {}
        };

        append_iterator(Container& ref):
                container(ref)
        {}

        constexpr append_iterator& operator++()
        {
            return *this;
        }

        constexpr append_iterator operator++(int)
        {
            return *this;
        }

        proxy operator*()
        {
            return proxy(container);
        }
    };
}

#endif //CUSTOM_LIBRARY_ITERATOR_HPP
