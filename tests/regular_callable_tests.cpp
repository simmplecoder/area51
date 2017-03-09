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
    static_assert(std::is_same<shino::regular_callable_t<regular_functor>, regular_functor>::value,
                  "regular_callable_t doesn't work correctly on regular functors");

    static_assert(std::is_same<shino::regular_callable_t<irregular_functor>, shino::callable_wrapper<irregular_functor>>::value,
                  "regular_callable_t doesn't work correctly on irregular functors");

    auto m = [](int x) {return x;};
    using lambda = decltype(m);

    static_assert(std::is_same<shino::regular_callable_t<lambda>, shino::callable_wrapper<lambda>>::value,
                  "regular_callable_t doesn't work correctly on lambdas");
}

