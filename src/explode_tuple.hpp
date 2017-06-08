#ifndef AREA51_TUPLE_EXPLODER_HPP
#define AREA51_TUPLE_EXPLODER_HPP

#include "utilities.hpp"

#include <tuple>
#include <functional>
#include <utility>
#include <type_traits>

namespace shino
{
    namespace detail
    {
        template <typename Functor, typename Tuple, std::size_t ... Indices>
        auto apply(Functor&& functor, Tuple&& tup, std::index_sequence<Indices...> = {})
        {
            return std::invoke(std::forward<Functor>(functor), std::get<Indices>(std::forward<Tuple>(tup))...);
        }
    }

    template <typename Functor, typename Tuple,
              typename IndexSequence = std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>>
    auto apply(Functor&& functor, Tuple&& tup, IndexSequence seq = {})
    {
        return detail::apply(std::forward<Functor>(functor), std::forward<Tuple>(tup), seq);
    }
}

#endif //AREA51_TUPLE_EXPLODER_HPP
