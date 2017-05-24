#ifndef AREA51_BENCHMARK_V2_HPP
#define AREA51_BENCHMARK_V2_HPP

#include "algorithm.hpp"
//#include "transform_iterator.hpp"
#include "utilities.hpp"

#include <experimental/filesystem>
#include <tuple>
#include <array>
#include <chrono>
#include <utility>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>

namespace shino
{
    template <typename Generator, typename ... Callables>
    class benchmark
    {
        Generator gen;
        std::tuple<Callables...> callables;
        std::vector<std::array<std::chrono::duration<double>, sizeof...(Callables)>> timings;
        std::vector<typename Generator::input_type> inputs;
    public:
        using input_type = typename Generator::input_type;
        static constexpr std::size_t function_count = sizeof...(Callables);

        template <typename Gen,
                  typename = shino::enable_sfinae<Gen, Generator>,
                  typename ... ArgTypes>
        benchmark(Gen&& generator, ArgTypes&& ... args):
                gen(std::forward<Gen>(generator)),
                callables(std::forward_as_tuple(std::forward<ArgTypes>(args)...))
        {}

        template <typename Gen,
                  typename = shino::enable_sfinae<Gen, Generator>,
                  typename Tuple>
        benchmark(Gen&& generator, Tuple&& tup):
                gen(std::forward<Gen>(generator)),
                callables(std::forward<Tuple>(tup))
        {}

        template <typename InputType,
                  typename = enable_sfinae<InputType, input_type>>
        void time(InputType&& input,
                  std::size_t runcount)
        {
            inputs.push_back(input);
            time_all(std::make_index_sequence<sizeof...(Callables)>{},
                     std::forward<InputType>(input), runcount);
        }

        template <typename OutputIterator,
                  typename Unit = std::chrono::milliseconds>
        void get_as(OutputIterator first)
        {
            for (const auto& timing : timings)
            {
                std::array<Unit, function_count> converted_readings;
                std::transform(timing.begin(), timing.end(), converted_readings.begin(),
                               [](const auto& reading) {
                                   return std::chrono::duration_cast<Unit>(reading);
                               });
                *first++ = converted_readings;
            }
        }

        template <typename Unit = std::chrono::milliseconds>
        auto get_as()
        {
            std::vector<std::array<Unit, function_count>> converted_readings(timings.size());

            get_as<Unit>(converted_readings.begin());
            return converted_readings;
        }

        template <typename Unit = std::chrono::milliseconds>
        void save_as(const std::string& metafilename,
                     const std::array<std::string, function_count>& filenames,
                     const std::string& xlabel = "Data size",
                     const std::string& ylabel = "Time")
        {
            std::experimental::filesystem::path metafilepath(metafilename);
            if (!metafilepath.has_filename())
            {
                throw std::invalid_argument("metafilename= " + metafilename + " is not a file");
            }

            metafilepath.remove_filename();
            std::experimental::filesystem::create_directories(metafilepath);

            std::ofstream metafile(metafilename);
            if (!metafile.is_open())
            {
                throw std::runtime_error("Couldn't create meta file. Does the folders in the path exist? "
                                                 "Library can't create folders for you if they don't exist");
            }

            metafile << xlabel << '\n';
            metafile << ylabel << '\n';

            for (const auto& filename : filenames)
            {
                metafile << filename << '\n';
            }

            if (!metafile.good())
            {
                //might be useful to check if the file was overridden
                throw std::runtime_error("Couldn't write everything to meta file, but opened it.");
            }

            for (std::size_t filenames_index = 0; filenames_index < filenames.size(); ++filenames_index)
            {
                auto filepath = metafilepath / filenames[filenames_index];
                const auto& filename = filepath.string();
                std::ofstream file(filename);

                if (!file.is_open())
                {
                    throw std::runtime_error("couldn't open one of the benchmark results file");
                }

                auto benchmark_name = filename;
                strip_directory(benchmark_name);
                strip_file_extension(benchmark_name);

                file << benchmark_name << '\n';

                for (std::size_t timings_index = 0; timings_index < timings.size(); ++timings_index)
                {
                    file << inputs[timings_index] << ' '
                         << std::chrono::duration_cast<Unit>(timings[timings_index][filenames_index]).count() << '\n';
                }

                if (!file.good())
                {
                    throw std::runtime_error("Could complete writing of " + filename);
                }
            }
        }

        auto timings_begin() const
        {
            return timings.begin();
        }

        auto timings_end() const
        {
            return timings.end();
        }

        auto inputs_begin() const
        {
            return inputs.begin();
        }

        auto inputs_end() const
        {
            return inputs.end();
        }

    private:
        void strip_file_extension(std::string& filename)
        {
            auto dot_location = shino::find_last_of(filename, '.');
            if (dot_location != std::string::npos)
            {
                filename.erase(dot_location);
            }
        }

        void strip_directory(std::string& filename)
        {
            auto last_slash_location = shino::find_last_of(filename, '/');
            if (last_slash_location != std::string::npos)
            {
                filename.erase(0, last_slash_location + 1);
            }
        }

        template <std::size_t Index, typename InputType,
                                     typename = enable_sfinae<InputType, input_type>>
        auto time_one(InputType&& input,
                      std::size_t runcount)
        {
            std::chrono::duration<double> timing(0);

            for (std::size_t i = 0; i < runcount; ++i)
            {
                auto callable_input = gen(input); //separate input creation from benchmark
                auto start = std::chrono::high_resolution_clock::now();
                shino::geniune_apply(std::get<Index>(callables), callable_input);
                auto end = std::chrono::high_resolution_clock::now();
                timing += end - start;
            }

            return timing / runcount;
        }

        template <std::size_t ... Indices,
                typename InputType,
                typename = shino::enable_sfinae<InputType, input_type>>
        void time_all(std::index_sequence<Indices...>,
                      InputType&& input,
                      std::size_t runcount)
        {
            std::array<std::chrono::duration<double>, sizeof...(Callables)> a_run =
                    {time_one<Indices>(std::forward<InputType>(input), runcount)...};
            timings.push_back(a_run);
        }
    };

    template <typename Gen, typename ... Callables>
    auto benchmarker(Gen&& generator, Callables&& ... callables)
    {
        return benchmark<std::decay_t<Gen>,
                std::decay_t<Callables>...>{std::forward<Gen>(generator),
                                            std::forward_as_tuple(std::forward<Callables>(callables)...)};
    }
}

#endif //AREA51_BENCHMARK_V2_HPP
