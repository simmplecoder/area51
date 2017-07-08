//
// Created by shino on 7/8/17.
//

#ifndef AREA51_FUNCTIONS_HPP
#define AREA51_FUNCTIONS_HPP

namespace shino
{
    /**
     * Behaves exactly as pre-increment on `int`s.
     * @tparam T type objects of whose to pre-increment.
     */
    template <typename T = void>
    struct pre_increment
    {
        /**
         * Mutates given value by pre-incrementing and returns.
         * a reference to the same value.
         * @param value value to mutate by pre-incrementing.
         * @return reference to pre-incremented `value`.
         */
        T& operator()(T& value)
        {
            return ++value;
        }
    };

    template <>
    struct pre_increment<void>
    {
        template <typename T>
        T& operator()(T& value)
        {
            return ++value;
        }
    };

    /**
     * Behaves exactly as post-increment on `int`s.
     * @tparam T type objects of whose to post-increment.
     */
    template <typename T = void>
    struct post_increment
    {
        /**
         * Mutates by post-incrementing given value and
         * returns it's previous state. Relies on post-increment
         * of the given `value` itself.
         * @param value value to post-increment.
         * @return `value` before post-incrementing.
         */
        T operator()(T& value)
        {
            return value++;
        }
    };

    template <>
    struct post_increment<void>
    {
        template <typename T>
        T operator()(T& value)
        {
            return value++;
        }
    };

    /**
     * Function object to do inplace multiplication by constant, e.g.
     * on calling `operator()` it will not return value,
     * but rather mutate it. Constant should be supplied during
     * construction. Infers type if `T = void`.
     * @tparam Arithmetic type of the constant to multiply by.
     * The type doesn't need to behave like arithmetic, but it makes
     * most sense that way.
     * @tparam T type objects of whose will be multiplied by a constant.
     */
    template <typename T = void, typename Arithmetic = int>
    class inplace_multiply_by
    {
        const Arithmetic value;
    public:
        /**
         * Initializes constant.
         * @param val value to set the constant to.
         */
        inplace_multiply_by(const Arithmetic& val):
                value(val)
        {}

        /**
         * @param init_value the value to mutate
         * by multiplying by a constant.
         */
        void operator()(T& init_value)
        {
            init_value *= value;
        }
    };

    template <typename Arithmetic>
    class inplace_multiply_by<void, Arithmetic>
    {
        const Arithmetic value;
    public:
        inplace_multiply_by(const Arithmetic& val):
                value(val)
        {}

        template <typename T>
        void operator()(T& init_value)
        {
            init_value *= value;
        }
    };

    /**
     * Function object to do inplace division by constant, e.g.
     * on caling `operator()` it will not return value,
     * but rather mutate it. Constant should be supplied during
     * construction.
     * @tparam Arithmetic type of the constant to divide by.
     * The type doesn't need to behave like arithmetic, but it makes
     * most sense that way.
     * @tparam T
     */
    template <typename T = void, typename Arithmetic = int>
    class inplace_divide_by
    {
        const Arithmetic value;
    public:
        /**
         * Initializes constant.
         * @param val value to set the  constant to.
         */
        inplace_divide_by(const Arithmetic& val):
                value(val)
        {}

        /**
         * @param init_value the value to mutate by
         * dividing by a constant.
         */
        void operator()(T& init_value)
        {
            init_value *= value;
        }
    };

    template <typename Arithmetic>
    class inplace_divide_by<Arithmetic>
    {
        const Arithmetic value;
    public:
        /**
         * Initializes constant.
         * @param val value to set the  constant to.
         */
        inplace_divide_by(const Arithmetic& val):
                value(val)
        {}

        /**
         * @param init_value the value to mutate by
         * dividing by a constant.
         */
         template <typename T>
        void operator()(T& init_value)
        {
            init_value *= value;
        }

    };
}

#endif //AREA51_FUNCTIONS_HPP
