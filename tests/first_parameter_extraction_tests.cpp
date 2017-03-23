#include "../src/deduce_first_parameter.hpp"

#include <vector>
#include <map>
#include <iostream>

struct dummy
{
    void operator()(std::vector<int>&) {}
    using correct_answer = std::vector<int>&;
};

struct not_so_dummy
{
    using correct_answer = const std::vector<std::map<int, char>>&;
    void operator()(const std::vector<std::map<int, char>>&) {}

};

void f(char, int);

int main()
{
#define error_msg "deducing first parameter failed"
    static_assert(std::is_same<deduce_first_parameter<decltype(f)>::type, char>::value, error_msg);
    static_assert(std::is_same<deduce_first_parameter<dummy>::type, dummy::correct_answer >::value, error_msg);
    static_assert(std::is_same<deduce_first_parameter<not_so_dummy>::type, not_so_dummy::correct_answer>::value,
                  error_msg);
#undef error_msg
    
    std::cerr << "test doesn't doesn't have runtime component. If it build correctly, it passed\n";
}
