#ifndef CUSTOM_LIBRARY_CUSTOM_MPL_H
#define CUSTOM_LIBRARY_CUSTOM_MPL_H

#include "typelist.hpp"

namespace shino
{
    template <typename QualifiedType, typename OriginalType>
    using sfinae_constraint = std::enable_if_t<std::is_same_v<std::decay_t<QualifiedType>, OriginalType>>;
}

#endif //CUSTOM_LIBRARY_CUSTOM_MPL_H
