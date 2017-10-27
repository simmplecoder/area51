#include <sort.hpp>
#include <random_int_generator.hpp>

#include <iostream>
#include <random>
#include <sstream>

class generator
{
    shino::random_int_generator<int, std::minstd_rand> gen;
public:
    using input_type = std::size_t;

    generator() :
            gen(0, 100'000)
    {}

    generator(generator&& other) :
            gen(std::move(other.gen))
    {}

    std::vector<int> operator()(input_type input)
    {
        static std::vector<int> v(input);
        if (v.size() != input)
        {
            v.resize(input);
            gen(v.begin(), v.end());
        }

        return v;
    }
};

const char* green_color = "\033[0;32m";
const char* red_color = "\033[0;31m";
const char* reset_color = "\033[0m";

constexpr std::size_t max_size = 10'000;

int main()
{
    generator gen;
    std::vector<std::size_t> failed_sizes;

    for (std::size_t i = 0; i <= max_size; ++i)
    {
        auto v = gen(i);
        shino::merge_sort(v.begin(), v.end());
        if (std::is_sorted(v.begin(), v.end()))
        {
            std::cout << green_color << "sorting a vector with size " << i << " succeeded\n"
                      << reset_color;
        }
        else
        {
            std::cout << red_color << "sorting a vector with size " << i << " failed\n"
                      << reset_color;
            failed_sizes.push_back(i);
        }
    }

    if (!failed_sizes.empty())
    {
        std::stringstream logstream;
        logstream << "merge sort failed for sizes {";
        auto first = failed_sizes.begin();
        auto last = failed_sizes.end();
        logstream << *first;
        ++first;

        while (first != last)
        {
            logstream << ", ";
            logstream << *first;
            ++first;
        }

        logstream << "}";
        throw std::logic_error(logstream.str());
    }
}

