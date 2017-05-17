#include "../src/benchmark_v2.hpp"
#include "../src/random_int_generator.hpp"
#include "../src/sort.hpp"
#include <cmath>
#include <iostream>
#include <memory>

class generator
{
    shino::random_int_generator<int, std::mt19937_64> gen;
public:
    using input_type = std::size_t;
    
    generator():
            gen(0, 100'000)
    {}
    
    generator(generator&& other):
            gen(std::move(other.gen))
    {}
    
    std::tuple<std::vector<int>, std::size_t> operator()(input_type input)
    {
        static std::vector<int> v(input);
        if (v.size() != input)
        {
            v.resize(input);
            gen(v.begin(), v.end());
        }
        
        return std::make_tuple(v, 0);
    }
};

class different_winsize_generator
{
    shino::random_int_generator<> gen;
    std::size_t vsize;
public:
    using input_type = std::size_t;

    different_winsize_generator(std::size_t size):
            vsize(size)
    {}

    different_winsize_generator(different_winsize_generator&& other):
            gen(std::move(other.gen)),
            vsize(other.vsize)
    {}

    std::tuple<std::vector<int>, std::size_t> operator()(input_type input)
    {
        static std::vector<int> v(vsize);
        static std::size_t window_length = input;
        if (window_length == input) //return cached value
        {
            return std::make_tuple(v, window_length);
        }
        window_length = input;
        std::uniform_int_distribution<std::size_t> dist(1, input - 1);
        for (int i = 0; i < v.size(); ++i)
        {
            v[i] = i;
        }

        for (std::size_t i = 0; i < v.size(); i += window_length)
        {
            std::shuffle(&v[i], &v[std::min(i + window_length, v.size())], gen.get_engine());
        }

        return std::make_tuple(v, window_length);
    }
};

int main()
{
    std::size_t counter = 0;
    auto combsort_bench = [&counter](std::vector<int>& v, std::size_t)
    {
        shino::comb_sort(v.begin(), v.end(), 1.3);
        std::cout << v.front() << ' ' << counter++ << '\n'; //just to tell compiler to not optimize the code away
    };

    auto stdsort_bench = [&counter](std::vector<int>& v, std::size_t)
    {
        std::sort(v.begin(), v.end());
        std::cout << v.front() << ' ' << counter++ << '\n'; //ditto
    };

//    auto simple_benchmark = shino::benchmarker(generator{}, combsort_bench, stdsort_bench);
//
//    for (std::size_t i = 1000; i <= 5'000; i += 5)
//    {
//        simple_benchmark.time(i, 3); //3 means runcount for the same dataset
//    }
//
//    simple_benchmark.save_as<std::chrono::microseconds>("./benchmarks/simple-benchmark/benchmarks.txt",
//                                                        {"./benchmarks/simple-benchmark/comb sort benchmark.txt",
//                                                         "./benchmarks/simple-benchmark/standard sort benchmark.txt"},
//                                                        "vector<int>.size()", "microseconds");
//
//    auto winsize_benchmark = shino::benchmarker(different_winsize_generator(10'000), combsort_bench, stdsort_bench);
//
//    for (std::size_t i = 1000; i <= 5'000; i += 5)
//    {
//        winsize_benchmark.time(i, 3); //3 means runcount for the same dataset
//    }
//
//    winsize_benchmark.save_as<std::chrono::microseconds>("./benchmarks/winsize-benchmark/benchmarks.txt",
//                                                        {"./benchmarks/winsize-benchmark/comb sort benchmark.txt",
//                                                         "./benchmarks/winsize-benchmark/standard sort benchmark.txt"},
//                                                        "window length",
//                                                        "microseconds");

    auto small_winsize_benchmark = shino::benchmarker(different_winsize_generator(50'000),
                                                      combsort_bench,
                                                      stdsort_bench);
    for (std::size_t i = 2; i <= 10; ++i)
    {
        small_winsize_benchmark.time(i, 3);
    }

    small_winsize_benchmark.save_as<std::chrono::microseconds>("./benchmarks/small-winsize-benchmark/benchmarks.txt",
                                                               {"./benchmarks/small-winsize-benchmark/comb sort benchmark.txt",
                                                               "./benchmarks/small-winsize-benchmark/standard sort benchmark.txt"},
                                                               "window length",
                                                               "microseconds");
}

