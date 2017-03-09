#ifndef AREA51_REGULAR_TYPE_HPP
#define AREA51_REGULAR_TYPE_HPP

#include <type_traits>
#include <memory>
#include <utility>

namespace shino {
    template<typename T>
    static constexpr bool Regular = std::is_default_constructible<T>::value &&
                                    (std::is_copy_constructible<T>::value ||
                                     std::is_move_constructible<T>::value) &&
                                    (std::is_copy_assignable<T>::value ||
                                     std::is_move_assignable<T>::value) &&
                                    std::is_destructible<T>::value;

    template<typename Callable>
    class callable_wrapper {
        std::shared_ptr<Callable> callable;
    public:
        template<typename Func, typename =
        std::enable_if_t<std::is_same<std::decay_t<Func>, Callable>::value, Func>>
        callable_wrapper(Func &&f):
                callable(std::make_unique<Callable>(std::forward<Func>(f))) {}

        template<typename ... ArgTypes>
        callable_wrapper(ArgTypes &&... args):
                callable(std::make_unique<Callable>(std::forward<ArgTypes>(args)...)) {}

        template<typename ... ArgTypes>
        auto operator()(ArgTypes &&... args) {
            return ((*callable))(std::forward<ArgTypes>(args)...);
        }

        template<typename ... ArgTypes>
        auto operator()(ArgTypes &&... args) const {
            return ((*callable))(std::forward<ArgTypes>(args)...);
        }
    };

    template<typename Callable>
    using regular_callable_t = std::conditional_t<Regular<Callable>, Callable, callable_wrapper<Callable>>;
}

#endif //AREA51_REGULAR_TYPE_HPP
