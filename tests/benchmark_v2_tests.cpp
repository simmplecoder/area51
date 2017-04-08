#include "../src/benchmark_v2.hpp"
#include "../src/random_int_generator.hpp"
#include <cmath>
#include <iostream>
#include <memory>

class generator
{
//    std::unique_ptr<shino::random_int_generator<int, std::mt19937_64>> gen;
    shino::random_int_generator<int, std::mt19937_64> gen;
public:
    using input_type = std::size_t;
    
    generator():
//            gen(std::make_unique<shino::random_int_generator<int, std::mt19937_64>>(0, 100'000))
            gen(0, 100'000)
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

#include <algorithm>

//code came from url : http://codereview.stackexchange.com/questions/157064/fast-quicksort-implementation
template<class iterator>
void quickSort(iterator begin, iterator end)
{
    if (end - begin > 1)
    {
        auto lpivot = begin + (end - begin) / 2;
        auto rpivot = lpivot;
        
        auto pValue = *lpivot;
        
        auto left_it = lpivot - 1;
        auto right_it = rpivot + 1;
        
        auto lValue = *left_it;
        auto rValue = *right_it;
        
        bool isGreater = false;
        bool isLess = false;
        
        while (left_it != begin-1 || right_it != end)
        {
            if (lValue >= pValue)
            {
                if (lValue == pValue)
                {
                    lpivot--;
                    std::iter_swap(lpivot, left_it);
                }
                else
                    isGreater = true;
            }
            
            if (rValue <= pValue)
            {
                if (rValue == pValue)
                {
                    rpivot++;
                    std::iter_swap(rpivot, right_it);
                }
                else
                    isLess = true;
            }
            if (isGreater && isLess)
            {
                std::iter_swap(left_it, right_it);
            }
            else if (isGreater)
            {
                if (left_it != lpivot - 1)
                    std::iter_swap(left_it, lpivot - 1);
                std::iter_swap(rpivot - 1, lpivot - 1);
                std::iter_swap(rpivot, rpivot - 1);
                lpivot--;
                rpivot--;
            }
            else if (isLess)
            {
                if (right_it != rpivot + 1)
                    std::iter_swap(right_it, rpivot + 1);
                std::iter_swap(lpivot + 1, rpivot + 1);
                std::iter_swap(lpivot, lpivot + 1);
                lpivot++;
                rpivot++;
            }
            
            if (left_it != begin - 1)
                left_it--;
            if (right_it != end)
                right_it++;
            
            lValue = *left_it;
            rValue = *right_it;
            
            isGreater = false;
            isLess = false;
        }
        
        quickSort(begin, lpivot);
        quickSort(rpivot + 1, end);
    }
}

int main()
{
    std::size_t counter = 0;
    auto quicksort_bench = [&counter](std::vector<int>& v)
    {
        quickSort(v.begin(), v.end());
        std::cout << v.front() << ' ' << counter++ << '\n'; //just to tell compiler to not optimize the code away
    };

    auto stdsort_bench = [&counter](std::vector<int>& v)
    {
        std::sort(v.begin(), v.end());
        std::cout << v.front() << ' ' << counter++ << '\n'; //ditto
    };

    auto checked_bench = shino::benchmarker(generator{}, quicksort_bench, stdsort_bench);

    for (std::size_t i = 1000; i <= 50'000; i += 100)
    {
        checked_bench.time(i, 3); //3 means runcount for the same dataset
    }

    checked_bench.save_as<std::chrono::microseconds>("./benchmarks/metafile.txt",
                          {"custom quicksort.txt", "standard sort.txt"});
}

