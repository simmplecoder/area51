//
// Created by olzhas on 2/21/17.
//

#ifndef SUNRISE_DEDUCE_SINGLE_PARAMETER_HPP
#define SUNRISE_DEDUCE_SINGLE_PARAMETER_HPP

template <typename FunctionPointer>
struct deduce_single_parameter;

template <typename R, typename T>
struct deduce_single_parameter<R(*)(T)>
{
    using type = T;
};

template <typename C, typename R, typename T>
struct deduce_single_parameter<R (C::*)(T)>
{
    using type = T;
};

template <typename FunctionPointer>
using deduce_single_parameter_t = typename deduce_single_parameter<FunctionPointer>::type;

#endif //SUNRISE_DEDUCE_SINGLE_PARAMETER_HPP
