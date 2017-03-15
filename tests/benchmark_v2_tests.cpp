#include "../src/benchmark_v2.hpp"
#include <cmath>

struct generator
{
    using input_type = int;

    std::tuple<int, int> operator()(input_type input)
    {
        return std::make_tuple(input, 20 - log2(input));
    }
};

int linear_pow(int base, int exponent)
{
    int result = 1;
    for (int i = 0; i < exponent; ++i)
    {
        result *= base;
    }

    return result;
}

int bin_pow(int base, int exponent)
{
    if (exponent == 0)
    {
        return 1;
    }

    if (exponent == 1)
    {
        return base;
    }

    if (exponent % 2 == 0)
    {
        int result = bin_pow(base, exponent / 2);
        return result * result;
    }
    else
    {
        int result = bin_pow(base, exponent - 1);
        return result * base;
    }
}

int main()
{
    auto linear_pow_bench = [](int base, int exponent)
    {
        for (int i = 0; i < 100; ++i)
        {
            linear_pow(base, exponent);
        }
    };

    auto bin_pow_bench = [](int base, int exponent)
    {
        for (int i = 0; i < 100; ++i)
        {
            bin_pow(base, exponent);
        }
    };

    auto checked_bench = shino::benchmarker(generator{}, linear_pow_bench, bin_pow_bench);

    for (int i = 1; i < 20; ++i)
    {
        checked_bench.time(i, 10);
    }

    checked_bench.save_as("./benchmarks/metafile.txt",
                          {"./benchmarks/linear power results.txt", "./benchmarks/binary power results.txt"});
}

