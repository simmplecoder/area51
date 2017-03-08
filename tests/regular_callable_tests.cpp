#include "../src/regular_callable.hpp"
#include <utility>

class regular_functor
{
    int operator()()
    {
        return 1;
    }
};

class irregular_functor
{
    irregular_functor(const irregular_functor& other) = delete;

    int operator()()
    {
        return 1;
    }
};

int main()
{
    static_assert(std::is_same<regular_callable_t<regular_functor>, regular_functor>::value,
                  "regular_callable_t doesn't work correctly");

    static_assert(std::is_same<regular_callable_t<irregular_functor>, callable_wrapper<irregular_functor>>::value,
                  "regular_callable_t doesn't work correctly");
}

