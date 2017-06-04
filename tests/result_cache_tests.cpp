#include "../src/result_cache.hpp"
#include "../src/random_int_generator.hpp"
#include "../src/benchmark_v2.hpp"
#include "../src/utilities.hpp"

#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

int add(int a, int b)
{
    return a + b;
}

std::vector<int> generate(std::size_t size)
{
    std::vector<int> v(size);
    for (std::size_t i = 0; i < size; ++i)
    {
        v[i] = (int) i;
    }

    return v;
}

int main()
{
    shino::result_cache<std::tuple<int, int>, int, int (*)(int, int)> cache(&add);
    shino::random_int_generator<> gen(0, 100);
    std::bernoulli_distribution dist;

    int a = gen(), b = gen();
    cache.update_cache(a, b);
    for (int i = 0; i < 10'000; ++i)
    {
        bool update_input = dist(gen.get_engine());
        if (update_input)
        {
            a = gen();
            b = gen();
            cache.update_cache(a, b);
        }

        int sum = a + b;
        if (sum != cache.get_value())
        {
            std::cerr << "Failing on test " << i << '\n' << "Cache doesn't store the values correctly\n";
            throw std::exception();
        }
    }

    auto another_cache = shino::result_cacher(add);
    static_assert(std::is_same_v<decltype(another_cache), decltype(cache)>, "result_cacher produces incorrect type");

    another_cache(a, b);
    for (int i = 0; i < 10'000; ++i)
    {
        bool update_input = dist(gen.get_engine());
        if (update_input)
        {
            a = gen();
            b = gen();
            another_cache(a, b);
        }

        int sum = a + b;
        if (sum != another_cache.get_value())
        {
            std::cerr << "Failing on test " << i << '\n' << "Cache doesn't store the values correctly\n";
            throw std::exception();
        }
    }
}

