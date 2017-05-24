#include "../src/utilities.hpp"
#include <utility>

int increment_both(int, int);
int decrement_both(int);

int main()
{
    //deduce_function_type tests
    using deduced_increment_function = shino::deduce_function_type<decltype(increment_both)>;
    using deduced_decrement_function = shino::deduce_function_type<decltype(decrement_both)>;

    static_assert(std::is_same_v<deduced_increment_function::return_type, int>,
                  "incorrectly deduced return type");
    static_assert(std::is_same_v<deduced_increment_function::tied_argument_types, std::tuple<int, int>>,
                  "incorrectly deduced argument types");

    static_assert(std::is_same_v<deduced_decrement_function::return_type, int>,
                                "incorrectly deduced return type");
    static_assert(std::is_same_v<deduced_decrement_function::tied_argument_types, std::tuple<int>>,
                  "incorrectly deduced argument types");

    static_assert(!std::is_same_v<deduced_increment_function, deduced_decrement_function>,
                  "incorrectly matching different functions");


}

