#ifndef AREA51_BENCHMARK_HPP
#define AREA51_BENCHMARK_HPP

#include <string>
#include <chrono>
#include <vector>
#include <utility>
#include "transform_iterator.hpp"

namespace shino {
    template<typename InputType, typename TimeUnit>
    struct benchmark_results {
        template<typename T, typename U>
        using xy_pairs = std::vector<std::pair<T, U>>;

        std::string xlabel_text;
        std::string ylabel_text;
        xy_pairs<InputType, TimeUnit> results;
    };

    template<typename Generator, typename Functor>
    class benchmarking_session {
        const std::string name;
        Generator generator;
        Functor functor;
        template<typename T, typename U>
        using xy_pairs = std::vector<std::pair<T, U>>;

        xy_pairs<typename Generator::input_type, std::chrono::duration<double>> timings;
    public:

        template <typename Gen, typename Func,
                typename = std::enable_if_t<std::is_same_v<std::decay_t<Gen>, Generator>>,
                typename = std::enable_if_t<std::is_same_v<std::decay_t<Func>, Functor>>>
        benchmarking_session(const std::string& benchname, Gen&& gen, Func&& func):
                name(benchname),
                generator(std::forward<Gen>(gen)),
                functor(std::forward<Func>(func))
        {}

        template <typename InputType,
                typename = std::enable_if_t<std::is_same_v<std::decay_t<InputType>, typename Generator::input_type>>>
        void time_once(InputType&& input)
        {
            auto generated_input = generator(std::forward<InputType>(input));
            auto start = std::chrono::high_resolution_clock::now();
            functor(generated_input);
            auto end = std::chrono::high_resolution_clock::now();
            timings.push_back(std::make_pair(input, end - start));
        }

        template<typename Unit = std::chrono::milliseconds>
        auto get_as(const std::string &xlabel_text, const std::string &ylabel_text) {
            auto converter = [](auto &reading) {
                auto converted_time = std::chrono::duration_cast<Unit>(reading.second);
                return std::make_pair(reading.first, converted_time);
            };

            xy_pairs<typename Generator::input_type, Unit> converted_timings(timings.size());
            auto convert_iterator = shino::transformer(converter, converted_timings.begin());
            std::copy(timings.begin(), timings.end(), convert_iterator);

            benchmark_results<typename Generator::input_type, Unit> results;
            results.results = std::move(converted_timings);
            results.xlabel_text = xlabel_text;
            results.ylabel_text = ylabel_text;

            return results;
        }
    };

    template<typename Generator, typename Functor>
    auto benchmarker(Generator&& generator, Functor&& functor, const std::string& benchname) {
        return benchmarking_session<std::remove_const_t<std::remove_reference_t<Generator>>,
                std::remove_const_t<std::remove_reference_t<Functor>>>(benchname,
                                                                       std::forward<Generator>(generator),
                                                                       std::forward<Functor>(functor));
        //NRVO will probably kick in
    }
}
#endif //AREA51_BENCHMARK_HPP
