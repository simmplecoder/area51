#ifndef SUNRISE_TRANSFORM_ITERATOR_HPP
#define SUNRISE_TRANSFORM_ITERATOR_HPP

#include <iterator>
#include <functional>

namespace shino
{
    template<typename Functor, typename Iterator>
    class transform_iterator :
            public std::iterator<std::output_iterator_tag,
                    void, void, void, void>
    {
        Functor functor;
        Iterator iterator;
    public:
        transform_iterator(const Functor& f, const Iterator& it) :
                functor(f),
                iterator(it)
        {}

        transform_iterator(Functor&& f, Iterator&& it) :
                functor(f),
                iterator(it)
        {}

        class proxy
        {
            friend class transform_iterator;

            Iterator &iterator;
            Functor &f;
        public:

            template <typename U>
            proxy &operator=(U&& value)
            {
                *iterator = std::__invoke(f, std::forward<U>(value));
                return *this;
            }

        private:
            proxy(Iterator &it, Functor &functor) :
                    iterator(it),
                    f(functor)
            {}
        };

        proxy operator*()
        {
            return proxy(iterator, functor);
        }

        transform_iterator &operator++()
        {
            ++iterator;
            return *this;
        }

        transform_iterator operator++(int)
        {
            auto copy = *this;
            ++iterator; //might exhibit different behavior sometimes
            return copy;
        }

        const Iterator& internal_iterator() const
        {
            return iterator;
        }

        const Functor& internal_functor() const
        {
            return functor;
        }

        void swap(transform_iterator& other)
        {
            using std::swap;
            swap(other.functor, functor);
            swap(other.iterator, iterator);
        }
    };

    template<typename Functor, typename Iterator>
    bool operator==(const transform_iterator<Functor, Iterator>& lhs,
                   const transform_iterator<Functor, Iterator>& rhs)
    {
        return lhs.internal_iterator() == rhs.internal_iterator();
    }

    template <typename Functor, typename Iterator>
    bool operator!=(const transform_iterator<Functor, Iterator>& lhs,
                    const transform_iterator<Functor, Iterator>& rhs)
    {
        return !(lhs == rhs);
    }

    template <typename Functor, typename Iterator>
    void swap(shino::transform_iterator<Functor, Iterator>& lhs,
              shino::transform_iterator<Functor, Iterator>& rhs)
    {
        lhs.swap(rhs);
    }

    template <typename Functor, typename Iterator>
    auto transformer(Functor&& f, Iterator&& iterator)
    {
        return transform_iterator<std::remove_const_t<std::remove_reference_t <Functor>>,
                std::remove_const_t<std::remove_reference_t<Iterator>>>(std::forward<Functor>(f),
                                                     std::forward<Iterator>(iterator));
    }
}



#endif //SUNRISE_TRANSFORM_ITERATOR_HPP
