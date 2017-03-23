#include "../src/benchmark.hpp"
#include "../src/benchmark_streamer.hpp"
#include <vector>
#include <iomanip>
#include <iostream>

class generator
{
public:
    using input_type = std::size_t;
    std::vector<std::size_t> operator()(std::size_t size)
    {
        std::vector<std::size_t> v(size);
        for (std::size_t i = 0; i < size; ++i)
        {
            v[i] = i;
        }

        return v;
    }
};

class functor
{
public:
    void operator()(const std::vector<std::size_t>& v)
    {
        std::vector<std::size_t> copy(v);
        for (std::size_t& number: copy)
        {
            number *= 2;
        }
    }
};

int main()
{
    auto session = shino::benchmarker(generator{}, functor{}, "Copy and Multiply");

    for (std::size_t i = 10'000; i < 1'000'000; i += 100)
    {
        constexpr std::size_t runcount = 5;
        session.time(i, runcount);
    }
    auto results = session.get_as<std::chrono::microseconds>("Vector_size", "Microseconds");

    shino::benchmark_streamer streamer;
    streamer << results;

    streamer.save("benchmark.txt", "Copying vector");
}
