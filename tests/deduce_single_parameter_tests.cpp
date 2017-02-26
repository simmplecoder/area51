#include "../src/deduce_single_parameter.hpp"
#include <string>
#include <vector>
#include <cassert>
#include <utility>
#include <type_traits>

int func0(const std::string&);
void func1(int);
void func2(const char*);

struct dummy_struct
{
    int do_smth(int);
    void get_lazy(std::string);
};

int main()
{
#define error_msg "parameter deducing failed"
    static_assert(std::is_same<deduce_single_parameter<decltype(&func0)>::type,
            const std::string&>::value, error_msg);
    static_assert(std::is_same<deduce_single_parameter<decltype(&func1)>::type,
            int>::value, error_msg);
    static_assert(std::is_same<deduce_single_parameter<decltype(&func2)>::type,
            const char*>::value, error_msg);

    static_assert(std::is_same<deduce_single_parameter<decltype(&dummy_struct::do_smth)>::type,
            int>::value, error_msg);
    static_assert(std::is_same<deduce_single_parameter_t<decltype(&dummy_struct::get_lazy)>,
            std::string>::value, error_msg);
#undef error_msg
}

