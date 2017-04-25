#include "../src/sort.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <random>
#include "../src/random_int_generator.hpp"

class generator
{
    shino::random_int_generator<int, std::mt19937_64> gen;
public:
    using input_type = std::size_t;

    generator(int a, int b):
            gen(a, b)
    {}

    generator(generator&& other):
            gen(std::move(other.gen))
    {}

    std::tuple<std::vector<int>> operator()(input_type input)
    {
        static std::vector<int> v(input);
        if (v.size() != input)
        {
            v.resize(input);
            (gen)(v.begin(), v.end());
        }

        return std::make_tuple(v);
    }
};



int main()
{
    generator gen(0, 100);
    constexpr std::size_t test_count = 10'000;
    std::vector<std::vector<int>> data(test_count);
    for (std::size_t i = 0; i < 4000; ++i)
    {
        data[i] = std::get<0>(gen(i)); //gen() returns tuple, 0th is vector
    }

    for (std::size_t i = 0; i <= 3000; ++i)
    {
        std::cout << "trying to sort vector with size " << i << '\n';
        shino::comb_sort(data[i].begin(), data[i].end(), 1.3);
        if (!std::is_sorted(data[i].begin(), data[i].end()))
        {
            std::cout << "vector is not sorted\n";
        }
    }
}