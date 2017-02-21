#deduce_single_parameter<>

The struct serves as type deducing tool. It acts much like standard deducing facilities, in a way that it provides `::type` type alias, as well as `deduce_single_parameter_t<>` typedef for easier use.

##Usage
>Given (member) function pointer, deduce the single parameter that it takes as input and provide it as alias `::type` or `deduce_single_parameter_t<>` alias.

As a result, it is not usable on overloaded or templated (member) function pointers. Type argument should be a function pointer, since there is no specialization for non pointer functions.

##Examples:

    #include "../src/deduce_single_parameter_tests.hpp"
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
        static_assert(std::is_same<deduce_single_parameter<decltype(&func0)>::type, const std::string&>::value);
        static_assert(std::is_same<deduce_single_parameter<decltype(&func1)>::type, int>::value);
        static_assert(std::is_same<deduce_single_parameter<decltype(&func2)>::type, const char*>::value);

        static_assert(std::is_same<deduce_single_parameter<decltype(&dummy_struct::do_smth)>::type, int>::value);
        static_assert(std::is_same<deduce_single_parameter_t<decltype(&dummy_struct::get_lazy)>, std::string>::value);
        //everything will compile correctly
}