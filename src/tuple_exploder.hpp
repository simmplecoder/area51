#ifndef AREA51_TUPLE_EXPLODER_HPP
#define AREA51_TUPLE_EXPLODER_HPP

#include <tuple>
#include <utility>
#include <type_traits>

template <typename Functor, typename ... ArgTypes>
std::result_of_t<Functor(ArgTypes...)> explode(Functor&& functor, std::tuple<ArgTypes...>& tuple)
{

}

#endif //AREA51_TUPLE_EXPLODER_HPP
