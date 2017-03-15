#ifndef AREA51_UTILITIES_HPP
#define AREA51_UTILITIES_HPP

namespace shino
{
    template <typename QualifiedType, typename OriginalType>
    using enable_sfinae = std::enable_if_t<std::is_same_v<std::decay_t<QualifiedType>, OriginalType>>;
}

#endif //AREA51_UTILITIES_HPP
