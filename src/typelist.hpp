#ifndef CUSTOM_LIBRARY_TYPELIST_HPP
#define CUSTOM_LIBRARY_TYPELIST_HPP

#include <cstddef>
#include <tuple>
#include <utility>
#include <cassert>

namespace shino
{
    template <class ... Types>
    class type_list
    {
    };

    template <std::size_t idx, class... Types>
    class extract
    {
        static_assert(idx < sizeof...(Types), "index out of bounds");

        template <std::size_t i, std::size_t n, class... Rest>
        struct extract_impl;

        template <std::size_t i, std::size_t n, class T, class... Rest>
        struct extract_impl<i, n, T, Rest...>
        {
            using type = typename extract_impl<i + 1, n, Rest...>::type;
        };

        template <std::size_t n, class T, class... Rest>
        struct extract_impl<n, n, T, Rest...>
        {
            using type = T;
        };
    public:
        using type = typename extract_impl<0, idx, Types...>::type;
    };

    template <std::size_t idx, class TypeList>
    struct type_list_extract;

    template <std::size_t idx, template <class...> class TypeList, class... Types>
    struct type_list_extract<idx, TypeList<Types...>>
    {
        using type = typename extract<idx, Types...>::type;
    };

    template <std::size_t idx, class TypeList>
    using type_list_extract_t = typename type_list_extract<idx, TypeList>::type;

    template <class FirstTypeList, class SecondTypeList>
    struct type_list_concat;

    template <template <class ...> class TypeList, class ... FirstTypesPack, class ... SecondTypesPack>
    struct type_list_concat<TypeList<FirstTypesPack...>, TypeList<SecondTypesPack...>>
    {
        using type = TypeList<FirstTypesPack..., SecondTypesPack...>;
    };

    template <class FirstTypeList, class SecondTypeList>
    using type_list_concat_t = typename type_list_concat<FirstTypeList, SecondTypeList>::type;

    template <class TypeList, size_t ... indexes>
    struct type_list_expand
    {
        using type = std::tuple<typename type_list_extract<indexes, TypeList>::type...>;
    };

    template <template <class...> class TypeList, class ... Types>
    struct type_list_expand<TypeList<Types...>>
    {
        using type = std::tuple<Types...>;
    };

    template <class TypeList, size_t ... indexes>
    using type_list_expand_t = typename type_list_expand<TypeList, indexes...>::type;
}
#endif //CUSTOM_LIBRARY_TYPELIST_HPP
