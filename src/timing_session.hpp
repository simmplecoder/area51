#ifndef TIMING_SESSION_HPP
#define TIMING_SESSION_HPP

#include <chrono>
#include <utility>
#include <vector>

template <class Func, class ... Args>
std::chrono::duration<double> measure(Func function, Args&& ... args)
{
    auto start = std::chrono::high_resolution_clock::now();
    function(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();

    return end - start;
}

template <typename Func>
class session
{
    Func function;
    std::vector<std::chrono::duration<double>> timings;
public:
    session(const Func& f) :
            function(f)
    {}

    session(Func&& f) :
            function(std::move(f))
    {}

    template <class ... Args>
    void measure(Args&& ... args)
    {
        auto start = std::chrono::high_resolution_clock::now();
        function(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();

        timings.push_back(end - start);

    }

    //writes into the range until either exhausts it or timings vector is exhausted
    template <typename Unit = std::chrono::milliseconds, typename OutputIt>
    void get_as(OutputIt first, OutputIt last)
    {
        auto it = timings.begin();
        for (; it != timings.end() && first != last;
               ++first, ++it)
        {
            *first = std::chrono::duration_cast<Unit>(*it);
        }
    }


};

#endif