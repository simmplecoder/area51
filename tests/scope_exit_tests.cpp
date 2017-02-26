#include "../src/scope_exit.hpp"
#include "../src/random_engine.hpp"
#include <cassert>
#include <type_traits>

void manipulate_counter(int &counter)
{
    scope_exit{++counter;};
    scope_exit{++counter;};
}

void check_capturing_behavior()
{
    int x = 0;
    int& x_ref = x;
    const int x_const = x;
    const int& x_const_ref = x_const;
    auto lambda = [&]()
    {
#define error_message "Behavior of capture by reference changed since the code was written"
        static_assert(std::is_same<decltype(x), int>::value, error_message);
        static_assert(std::is_same<decltype(x_ref), int&>::value, error_message);
        static_assert(std::is_same<decltype(x_const), const int>::value, error_message);
        static_assert(std::is_same<decltype(x_const_ref), const int&>::value, error_message);
#undef error_message
    };

    lambda();
}

void counter_test(int count)
{
    int counter = 0;
    for (int i = 0; i < count; ++i)
    {
        manipulate_counter(counter);
    }

    assert(counter == count * 2);
    counter = 0;
}

struct copy_checker
{
    bool copied;
    copy_checker():
            copied(false)
    {}

    copy_checker(const copy_checker& other):
            copied(true)
    {
        (void)other;
    }
};

void copy_check()
{
    copy_checker checker;

    scope_exit
    {
        assert(!checker.copied); //triggering this means that lambda captures by copy
    };
}

void run_tests()
{
    shino::random_int_generator<> gen(0, 20'000);

    constexpr std::size_t test_count = 100;
    for (std::size_t i = 0; i < test_count; ++i)
    {
        counter_test(gen());
    }

    check_capturing_behavior();
    copy_check();
}

int main()
{
    run_tests();
}
