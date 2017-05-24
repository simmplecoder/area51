#ifndef AREA51_UTILITIES_HPP
#define AREA51_UTILITIES_HPP

#include <tuple>
#include <array>

namespace shino
{

    template <typename QualifiedType, typename OriginalType>
    using enable_sfinae = std::enable_if_t<std::is_same_v<std::decay_t<QualifiedType>, OriginalType>>;

    template <typename T>
    struct is_straight_tuple
    {
        static constexpr bool value = false;

        constexpr operator bool()
        {
            return value;
        }
    };

    template <typename ... Ts>
    struct is_straight_tuple<std::tuple<Ts...>>
    {
        static constexpr bool value = true;

        constexpr operator bool()
        {
            return value;
        }
    };

    template <typename T>
    struct is_std_array : public std::false_type
    {
    };

    template <typename T, std::size_t size>
    struct is_std_array<std::array<T, size>> : public std::true_type
    {
    };

    template <typename T>
    struct is_tuple_like : public std::bool_constant<is_std_array<T>::value || is_straight_tuple<T>::value>
    {
//        static constexpr bool value = is_std_array<T>::value || is_straight_tuple<T>::value;
//
//        constexpr operator bool()
//        {
//            return value;
//        }
    };

//    template <typename T, std::size_t size>
//    struct is_tuple_like<T[size]>
//    {
//        static constexpr bool value = true;
//
//        constexpr operator bool()
//        {
//            return value;
//        }
//    };

//    template <typename Callable, typename T, typename = std::enable_if_t<shino::is_straight_tuple<T>>>
//    auto geniune_apply(Callable&& callable, T&& argument)
//    {
//        return std::apply(std::forward<Callable>(callable), std::forward<T>(argument));
//    }

//    template <typename Callable, typename ... Ts>
//    auto geniune_apply(Callable&& callable, std::tuple<Ts...>&& arg)
//    {
//        return std::apply(std::forward<Callable>(callable), std::forward<std::tuple<Ts...>>(arg));
//    }

    namespace detail
    {
        template <typename Callable, typename Tuple>
        decltype(auto) geniune_apply(Callable&& callable, Tuple&& tuple, std::true_type)
        {
            return std::apply(std::forward<Callable>(callable), std::forward<Tuple>(tuple));
        }

        template <typename Callable, typename Tuple>
        decltype(auto) geniune_apply(Callable&& callable, Tuple&& tuple, std::false_type)
        {
            return std::forward<Callable>(callable)(std::forward<Tuple>(tuple));
        }
    }

//    template <typename Callable, typename Tuple>
//    auto geniune_apply(Callable&& callable, Tuple&& tuple)
//    {
//        return std::apply(std::forward<Callable>(callable), std::forward<Tuple>(tuple));
//    }
//
//    template <typename Callable, typename T, typename = typename std::enable_if<!shino::is_tuple_like<std::decay_t<T>>::value>::type>
//    auto geniune_apply(Callable&& callable, T&& arg)
//    {
//        return std::forward<Callable>(callable)(std::forward<T>(arg));
//    }
    template <typename Callable, typename T>
    decltype(auto) geniune_apply(Callable&& callable, T&& argument)
    {
        return detail::geniune_apply(std::forward<Callable>(callable), std::forward<T>(argument),
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
