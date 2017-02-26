#ifndef CUSTOM_LIBRARY_ITERATOR_HPP
#define CUSTOM_LIBRARY_ITERATOR_HPP

#include <experimental/optional>
#include <iterator>

namespace shino {
    template<typename T>
    class stumbled_iterator : public std::iterator<std::input_iterator_tag, T>
    {
        std::experimental::optional<const T> value;
        std::size_t count;
    public:
        stumbled_iterator(const T &val, std::size_t count_) :
                value(val),
                count(count_)
        {}

        stumbled_iterator(T&& val, std::size_t count_):
                value(val),
                count(count_)
        {}

        stumbled_iterator() :
                count(0)
        {}

        stumbled_iterator &operator++() {
            --count;
            return *this;
        }

        stumbled_iterator operator++(int) {
            auto copy = *this;
            --count;
            return copy;
        }

        const T& operator*() {
            return *value;
        }

        template <typename U>
        friend bool operator==(const stumbled_iterator<U>& lhs, const stumbled_iterator<U>& rhs);
    };

    template <>
    class stumbled_iterator<void> {};

    template <typename T>
    bool operator==(const stumbled_iterator<T>& lhs, const stumbled_iterator<T>& rhs)
    {
        return lhs.count == rhs.count;
    }

    template <typename T>
    bool operator!=(const stumbled_iterator<T>& lhs, const stumbled_iterator<T>& rhs)
    {
        return !(lhs == rhs);
    }

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
                return *this;
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
