#ifndef AREA51_UTILITIES_HPP
#define AREA51_UTILITIES_HPP

#include <tuple>
#include <array>

namespace shino
{

    template <typename QualifiedType, typename OriginalType>
    using enable_sfinae = std::enable_if_t<std::is_same_v<std::decay_t<QualifiedType>, OriginalType>>;

    template <typename T>
    struct is_straight_tuple : public std::false_type
    {};

    template <typename ... Ts>
    struct is_straight_tuple<std::tuple<Ts...>> : public std::true_type
    {};

    template <typename T>
    struct is_std_array : public std::false_type
    {};

    template <typename T, std::size_t size>
    struct is_std_array<std::array<T, size>> : public std::true_type
    {};

    template <typename T>
    struct is_tuple_like : public std::bool_constant<is_std_array<T>::value || is_straight_tuple<T>::value>
    {};

    namespace detail
    {
        template <typename Callable, typename Tuple>
        decltype(auto) genuine_apply(Callable&& callable, Tuple&& tuple, std::true_type)
        {
            return std::apply(std::forward<Callable>(callable), std::forward<Tuple>(tuple));
        }

        template <typename Callable, typename Tuple>
        decltype(auto) genuine_apply(Callable&& callable, Tuple&& tuple, std::false_type)
        {
            return std::forward<Callable>(callable)(std::forward<Tuple>(tuple));
        }
    }

    template <typename Callable, typename T>
    decltype(auto) genuine_apply(Callable&& callable, T&& argument)
    {
        return detail::genuine_apply(std::forward<Callable>(callable), std::forward<T>(argument),
                                     is_tuple_like<std::decay_t<T>>{});
    };

    template <typename Function>
    struct deduce_function_type;

    template <typename R, typename ... ArgTypes>
    struct deduce_function_type<R(ArgTypes...)>
    {
        using return_type = R;
        using tied_argument_types = std::tuple<ArgTypes...>;
    };
}

#endif //AREA51_UTILITIES_HPP
