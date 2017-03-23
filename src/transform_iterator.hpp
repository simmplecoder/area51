#ifndef SUNRISE_TRANSFORM_ITERATOR_HPP
#define SUNRISE_TRANSFORM_ITERATOR_HPP

#include "regular_callable.hpp"

#include <iterator>
#include <functional>

namespace shino {
    template<typename T>
    struct placeholder {
    };

    template<typename Functor, typename Iterator>
    class transform_iterator :
            public std::iterator<std::output_iterator_tag,
                    void, void, void, void> {
        regular_callable_t<Functor> functor;
        Iterator iterator;
    public:
        template<typename Func, typename It,
                typename = std::enable_if_t<std::is_same<std::decay_t<Func>, Functor>::value>,
                typename =  std::enable_if_t<std::is_same<std::decay_t<It>, Iterator>::value>>
        transform_iterator(Func &&f, It &&it) :
                functor(std::forward<Func>(f)),
                iterator(std::forward<It>(it)) {}

        template<typename It, typename ... ArgTypes,
                typename = std::enable_if_t<std::is_same<std::decay_t<It>, Iterator>::value, It>>
        transform_iterator(It &&it, ArgTypes &&... args):
                functor(std::forward<ArgTypes>(args)...),
                iterator(std::forward<It>(it)) {}

        class proxy {
            friend class transform_iterator;

            Iterator& iterator;
            regular_callable_t <Functor>& f;
        public:

            template<typename U>
            proxy &operator=(U &&value) {
                *iterator = std::invoke(f, std::forward<U>(value));
                return *this;
            }

        private:
            proxy(Iterator &it, regular_callable_t <Functor> &proxy_functor) :
                    iterator(it),
                    f(proxy_functor) {}
        };

        proxy operator*() {
            return proxy(iterator, functor);
        }

        transform_iterator &operator++() {
            ++iterator;
            return *this;
        }

        transform_iterator operator++(int) {
            auto copy = *this;
            ++iterator; //might exhibit different behavior sometimes
            return copy;
        }

        const Iterator &internal_iterator() const {
            return iterator;
        }

        const Functor &internal_functor() const {
            return functor;
        }

        void swap(transform_iterator &other) {
            using std::swap;
            swap(other.functor, functor);
            swap(other.iterator, iterator);
        }
    };

    template<typename Functor, typename Iterator>
    bool operator==(const transform_iterator<Functor, Iterator> &lhs,
                    const transform_iterator<Functor, Iterator> &rhs) {
        return lhs.internal_iterator() == rhs.internal_iterator();
    }

    template<typename Functor, typename Iterator>
    bool operator!=(const transform_iterator<Functor, Iterator> &lhs,
                    const transform_iterator<Functor, Iterator> &rhs) {
        return !(lhs == rhs);
    }

    template<typename Functor, typename Iterator>
    void swap(shino::transform_iterator<Functor, Iterator> &lhs,
              shino::transform_iterator<Functor, Iterator> &rhs) {
        lhs.swap(rhs);
    }

    template<typename Functor, typename Iterator>
    auto transformer(Functor &&f, Iterator &&iterator) {
        return transform_iterator<std::decay_t<Functor>,
                std::decay_t<Iterator>>(std::forward<Functor>(f), std::forward<Iterator>(iterator));
    }
}



#endif //SUNRISE_TRANSFORM_ITERATOR_HPP
