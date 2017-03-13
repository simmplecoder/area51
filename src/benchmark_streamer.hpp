#ifndef AREA51_BENCHMARK_ASSEMBLER_HPP
#define AREA51_BENCHMARK_ASSEMBLER_HPP

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include "benchmark.hpp"

namespace shino {
    class benchmark_streamer {
    std::stringstream sstream;
    public:
        void save(const std::string &filename, const std::string &benchname) {
            std::ofstream benchmarks_file(filename);
            if (!benchmarks_file.is_open()) {
                throw std::runtime_error("file opening failed.");
            }

            benchmarks_file << benchname << '\n';
            benchmarks_file << sstream.str();
        }

        template<typename InputType, typename TimeUnit>
        friend benchmark_streamer &operator<<(benchmark_streamer &bs,
                                              benchmark_results <InputType, TimeUnit> results) {
            bs.sstream << results.xlabel_text << ' ' << results.ylabel_text << '\n';
            for (const auto &reading: results.results) {
                bs.sstream << reading.first << ' ' << reading.second.count() << '\n';
            }

            return bs;
        }
    };
}

#endif //AREA51_BENCHMARK_ASSEMBLER_HPP
