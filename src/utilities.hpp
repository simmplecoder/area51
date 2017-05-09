#ifndef AREA51_UTILITIES_HPP
#define AREA51_UTILITIES_HPP

#include <tuple>
#include <array>

namespace shino
{
    namespace details
    {
        
    }
    
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
    struct is_std_array
    {
        static constexpr bool value = false;
    };
    
    template <typename T, std::size_t size>
    struct is_std_array<std::array<T, size>>
    {
        static constexpr bool value = true;
        
        constexpr operator bool()
        {
            return value;
        }
    };
    
    template <typename T>
    struct is_tuple_like
    {
        static constexpr bool value = is_std_array<T>::value || is_straight_tuple<T>::value;
    
        constexpr operator bool()
        {
            return value;
        }
    };
    
    template <typename T, std::size_t size>
    struct is_tuple_like<T[size]>
    {
        static constexpr bool value = true;
    
        constexpr operator bool()
        {
            return value;
        }
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
