#ifndef SUNRISE_DEDUCE_FIRST_PARAMETER_HPP
#define SUNRISE_DEDUCE_FIRST_PARAMETER_HPP

template <typename ... Args>
struct pick_first;

template <typename T, typename ... Args>
struct pick_first<T, Args ...>
{
    using type = T;
};

template <typename ... Args>
using pick_first_t = typename pick_first<Args...>::type;

template <typename Callable>
struct deduce_first_parameter
{
private:
    template <typename Func, template <typename ...> typename Operation>
    struct extract_function;

    template <typename R, typename ... Args, template <typename ...> typename Operation>
    struct extract_function<R(Args...), Operation>
    {
        using type = typename Operation<Args...>::type;
    };

    template <typename C, typename R, typename ... Args, template <typename ...> typename Operation>
    struct extract_function<R (C::*)(Args...), Operation>
    {
        using type = typename Operation<Args...>::type;
    };

    template <typename Func, template <typename ...> typename Operation>
    using extract_function_t = typename extract_function<Func, Operation>::type;

public:
    using type = extract_function_t<decltype(&Callable::operator()), pick_first>;
};

template <typename R, typename ... InputArgs>
struct deduce_first_parameter<R(InputArgs...)>
{
    using type = pick_first_t<InputArgs...>;
};

#endif //SUNRISE_DEDUCE_FIRST_PARAMETER_HPP
