#ifndef SUNRISE_PREPROCESSING_ITERATOR_HPP
#define SUNRISE_PREPROCESSING_ITERATOR_HPP

#include <iterator>

namespace shino
{
    template<typename Functor, typename InputType, typename Iterator>
    class transform_iterator :
            public std::iterator<std::output_iterator_tag,
                    InputType, void, void, void>
    {
        Functor functor;

        Iterator iterator;
    public:
        transform_iterator(const Functor &f, const Iterator &it) :
                functor(f),
                iterator(it)
        {}

        transform_iterator(Functor &&f, Iterator &&it) :
                functor(f),
                iterator(it)
        {}

        class proxy
        {
            friend class transform_iterator;

            Iterator &iterator;
            Functor &f;
        public:
            using value_type = InputType;

            proxy &operator=(const value_type &value)
            {
                *iterator = f(value);
                return *this;
            }

            proxy &operator=(value_type &&value)
            {
                *iterator = f(value);
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

    template<typename Functor, typename InputType, typename Iterator>
    bool operator==(const transform_iterator<Functor, InputType, Iterator>& lhs,
                   const transform_iterator<Functor, InputType, Iterator>& rhs)
    {
        return lhs.internal_iterator() == rhs.internal_iterator();
    };

    template <typename Functor, typename InputType, typename Iterator>
    bool operator!=(const transform_iterator<Functor, InputType, Iterator>& lhs,
                    const transform_iterator<Functor, InputType, Iterator>& rhs)
    {
        return !(lhs == rhs);
    };
}

namespace std
{
    template <typename Functor, typename InputType, typename Iterator>
    void swap(shino::transform_iterator<Functor, InputType, Iterator>& lhs,
              shino::transform_iterator<Functor, InputType, Iterator>& rhs)
    {
        lhs.swap(rhs);
    };
}



#endif //SUNRISE_PREPROCESSING_ITERATOR_HPP
