#ifndef SUNRISE_PREPROCESSING_ITERATOR_HPP
#define SUNRISE_PREPROCESSING_ITERATOR_HPP

#include <iterator>

namespace shino
{
/**
 * @class preprocessing_iterator
 * @brief an output iterator that applies a functor to input before assigning to underlying iterator
 *
 * @tparam Functor - functor that should be applied before assigning to underlying container.
 * @tparam InputType - type that functor accepts.
 * @tparam Iterator - underlying iterator type to which result be assigned
 *
 * The iterator creates sort of facade over the supplied iterator, making it possible
 * to preprocess data before writing it into the iterator range. One of the best use cases
 * would be when input range has type T and to convert to type U a function should be called
 * on all elements of the range. `InputType` is not mandated to be the only parameter type of the `Callable`,
 * so it will be possible to do something like recursion with it. Functor should be lightweight to copy
 * since iterators are copied a lot. `InputType` should not be cv qualified.
 */
    template<typename Functor, typename InputType, typename Iterator>
    class preprocessing_iterator :
            public std::iterator<std::output_iterator_tag,
                    InputType, void, void, void>
    {
        /**
         * @var
         * @brief Underlying functor stored by value to avoid lifetime issues
         *
         * Functor has to be lightweight as a result
         * */
        Functor functor;

        /**
         * @var
         * @brief Underlying iterator
         *
         * Iterator can have any `value_type` as long as it is implicitly convertible
         * result of the `decltype(functor())`
         */
        Iterator iterator;
    public:
        preprocessing_iterator(const Functor &f, const Iterator &it) :
                functor(f),
                iterator(it)
        {}

        preprocessing_iterator(Functor &&f, Iterator &&it) :
                functor(f),
                iterator(it)
        {}

        /**
         * @class proxy
         * @brief serves as a return type of `operator*()` of preprocessing iterator. Performs most of the logic.
         *
         * proxy defines the incoming type, since proxy is the receiver. It immediately applies functor
         * and assigns result to underlying iterator.
         */
        class proxy
        {
            friend class preprocessing_iterator;

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
            /**
             * @fn constructor
             * @brief Private constructor because proxy shouldn't be usable outside
             *
             * proxy is meant to be invisible, so hiding conversion constructors.
             * */
            proxy(Iterator &it, Functor &functor) :
                    iterator(it),
                    f(functor)
            {}
        };

        proxy operator*()
        {
            return proxy(iterator, functor);
        }

        preprocessing_iterator &operator++()
        {
            ++iterator;
            return *this;
        }

        preprocessing_iterator operator++(int)
        {
            auto copy = *this;
            ++iterator; //might exhibit different behavior sometimes
            return *this;
        }

        /**
         * @return underlying iterator
         *
         * Compatibility function, might be used to retrieve results stored in iterator
         */
        Iterator internal_iterator()
        {
            return iterator;
        }

        /**
         * @return underlying functor
         *
         * Compatibility function, might be used to retrieve results stored in functor
         */
        Functor internal_functor()
        {
            return functor;
        }
    };
}

#endif //SUNRISE_PREPROCESSING_ITERATOR_HPP
