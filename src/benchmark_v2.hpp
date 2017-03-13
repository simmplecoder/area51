#ifndef AREA51_BENCHMARK_V2_HPP
#define AREA51_BENCHMARK_V2_HPP

#include <tuple>
#include <array>
#include <chrono>
#include <utility>
#include <vector>
#include "transform_iterator.hpp"

namespace shino {
    template<typename Generator, typename ... Callables>
    class benchmark {
        Generator gen;
        std::tuple<Callables...> callables;
        std::vector<std::array<std::chrono::duration<double>, sizeof...(Callables)>> timings;
    public:
        using input_type = typename Generator::input_type;
        static constexpr std::size_t function_count = sizeof...(Callables);

        template<typename Gen, typename = std::enable_if_t<std::is_same_v<std::decay_t<Gen>, Generator>>,
                typename ... ArgTypes>
        benchmark(Gen &&generator, ArgTypes &&... args):
                gen(std::forward<Gen>(generator)),
                callables(std::forward_as_tuple(std::forward<ArgTypes>(args)...)) {}

        template<typename Gen, typename = std::enable_if_t<std::is_same_v<std::decay_t<Gen>, Generator>>,
                typename Tuple>
        benchmark(Gen &&generator, Tuple &&tup):
                gen(std::forward<Gen>(generator)),
                callables(std::forward<Tuple>(tup)) {}

        template<typename InputType, typename = std::enable_if_t<std::is_same_v<std::decay_t<InputType>, input_type>>>
        void time(InputType &&input, std::size_t runcount) {
            time_all(std::make_index_sequence<sizeof...(Callables)>{},
                     std::forward<InputType>(input), runcount);
        }

        template<typename OutputIterator, typename Unit = std::chrono::milliseconds>
        void get_as(OutputIterator first) {
            auto converter = [](const auto &readings) {
                std::array<Unit, function_count> converted_readings;
                std::transform(readings.begin(), readings.end(), converted_readings.begin(),
                               [](const auto &reading) {
                                   return std::chrono::duration_cast<Unit>(reading);
                               }
                );
            };

            auto converting_iterator = shino::transformer(converter, first);
            std::copy(timings.begin(), timings.end(), converting_iterator);
        }

        template<typename Unit = std::chrono::milliseconds>
        void get_as() {
            std::vector<std::array<Unit, function_count>> converted_readings(timings.size());

            auto converter = [](const auto &readings) {
                std::array<Unit, function_count> converted_readings;
                std::transform(readings.begin(), readings.end(), converted_readings.begin(),
                               [](const auto &reading) {
                                   return std::chrono::duration_cast<Unit>(reading);
                               }
                );
            };

            auto converting_iterator = shino::transformer(converter, converted_readings.begin());
            std::copy(timings.begin(), timings.end(), converting_iterator);
        }

    private:
        template<std::size_t Index, typename InputType,
                typename = std::enable_if_t<std::is_same_v<std::decay_t<InputType>, input_type>>>
        auto time_one(InputType &&input, std::size_t runcount) {
            std::chrono::duration<double> timing(0);

            for (std::size_t i = 0; i < runcount; ++i) {
                auto callable_input = gen(input);
                auto start = std::chrono::high_resolution_clock::now();
                std::apply(std::get<Index>(callables), callable_input);
                auto end = std::chrono::high_resolution_clock::now();
                timing += end - start;
            }

            return timing / runcount;
        }

        template<std::size_t ... Indices,
                typename InputType, typename = std::enable_if_t<std::is_same_v<std::decay_t<InputType>, input_type>>>
        void time_all(std::index_sequence<Indices...>, InputType &&input, std::size_t runcount) {
            std::array<std::chrono::duration<double>, sizeof...(Callables)> a_run =
                    {time_one<Indices>(std::forward<InputType>(input), runcount)...};
            timings.push_back(a_run);
        }
    };

    template<typename Gen, typename ... Callables>
    auto benchmarker(Gen &&generator, Callables &&... callables) {
        return benchmark<std::decay_t<Gen>,
                std::decay_t<Callables>...>{std::forward<Gen>(generator),
                                            std::forward_as_tuple(std::forward<Callables>(callables)...)};
    }
}

#endif //AREA51_BENCHMARK_V2_HPP
