#ifndef AREA51_SMALL_CACHE_HPP
#define AREA51_SMALL_CACHE_HPP

#include "utilities.hpp"

#include <tuple>
#include <functional>

namespace shino
{

    template <typename Key, typename ValueType, typename Callable>
    class result_cache
    {
        Callable current_callable;
        Key current_key;
        ValueType current_value;
    public:
        using input_type = Key;

        result_cache(Callable&& callable = Callable(),
                     Key&& key = Key(),
                     ValueType&& value = ValueType()) :
                current_callable(std::forward<Callable>(callable)),
                current_key(std::forward<Key>(key)),
                current_value(std::forward<ValueType>(value))
        {}

        template <typename ... Args>
        ValueType& update_cache(Args&& ... args)
        {
            auto tup = std::tie(args...);
            if (tup != current_key)
            {
                current_value = std::invoke(current_callable, args...);
                current_key = tup;
            }

            return current_value;
        }

        template <typename ... ArgTypes>
        ValueType& operator()(ArgTypes&& ... args)
        {
            auto tied_args = std::tie(args...);
            if (tied_args != current_key)
            {
                current_value = std::invoke(current_callable, std::forward<ArgTypes>(args)...);
                current_key = tied_args;
            }

            return current_value;
        }

        ValueType& get_value() noexcept
        {
            return current_value;
        }

        const ValueType& get_value() const noexcept
        {
            return current_value;
        }

        Key& get_key() noexcept
        {
            return current_key;
        }

        const Key& get_key() const noexcept
        {
            return current_key;
        }
    };

    template <typename Func>
    auto result_cacher(Func&& f)
    {
        using decayed_func_ptr = std::decay_t<Func>;
        using decayed_func = std::remove_pointer_t<decayed_func_ptr>;
        using deduced_function_type = deduce_function_type<decayed_func>;
        return result_cache<typename deduced_function_type::tied_argument_types,
                typename deduced_function_type::return_type,
                decayed_func_ptr>(std::forward<Func>(f));
    }
}

#endif //AREA51_SMALL_CACHE_HPP
