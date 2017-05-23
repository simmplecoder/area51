#ifndef AREA51_DEF_FORMATTER_HPP
#define AREA51_DEF_FORMATTER_HPP

#include "../benchmark_v2.hpp"
#include <experimental/filesystem>

#include <string>
#include <array>
#include <sstream>
#include <chrono>
#include <iostream>
#include <fstream>

namespace shino
{
    struct title
    {
        std::string name;
    };

    struct x_label
    {
        std::string label;
    };

    struct y_label
    {
        std::string label;
    };

    namespace fsystem = std::experimental::filesystem;

    std::string current_datetime()
    {
        std::time_t current_datetime;
        time(&current_datetime);
        std::string res(std::ctime(&current_datetime));
        if (res.back() == '\n') { //sometimes happens
            res.pop_back();
        }
        return res;
    }

    class def_formatter
    {
        std::string m_title;
        std::string m_x_label;
        std::string m_y_label;

    public:
        def_formatter():
                m_title("benchmark"),
                m_x_label("data size"),
                m_y_label("time taken")
        {}

        def_formatter(const def_formatter& other) = delete;
        def_formatter &operator=(const def_formatter& other) = delete;

        def_formatter(def_formatter&& other) = default;
        def_formatter &operator=(def_formatter&& other) = default;

        void change_title(const std::string& title)
        {
            m_title = title;
        }

        void change_x_label(const std::string& x_label)
        {
            m_x_label = x_label;
        }

        void change_y_label(const std::string& y_label)
        {
            m_y_label = y_label;
        }

        template <typename TimeUnit, typename Generator, typename ... Callables>
        void format_as(const benchmark<Generator, Callables...>& benchmark,
                    const std::array<std::string, sizeof...(Callables)>& filenames,
                    const std::string& root_path = current_datetime())
        {
            std::experimental::filesystem::path path(root_path);


            //no check, since its ok if it returns false, but not ok if throws
            std::experimental::filesystem::create_directories(path);

            auto processed_fnames = process_fnames(filenames);
            create_metafile(path, processed_fnames);

            for (std::size_t i = 0; i < sizeof...(Callables); ++i)
            {
                auto filepath = path/processed_fnames[i];
                create_bench_file<TimeUnit>(filepath, i,
                                  benchmark.inputs_begin(), benchmark.inputs_end(),
                                  benchmark.timings_begin(), benchmark.timings_end());
            }
        }

    private:
        template <std::size_t size>
        std::array<fsystem::path, size> process_fnames(const std::array<std::string, size>& fnames)
        {
            std::array<fsystem::path, size> processed_fnames;
            for (std::size_t i = 0; i < size; ++i)
            {
                fsystem::path p(fnames[i]);

                //if nothing of the below hits, it is ok
                if (!p.has_filename())
                {
                    std::cerr << "the argument doesn't have filename, replacing with "
                              "function " + std::to_string(i);
                    p.clear();
                    p /= "function " + std::to_string(i);
                }
                else if (p.filename() != p)
                {
                    std::cerr << "the argument contains additional path, discarding non-filename part\n";
                    p = p.filename();
                }

                processed_fnames[i] = p;
            }

            return processed_fnames;
        }

        template <std::size_t size>
        void create_metafile(const fsystem::path& root_path,
                             const std::array<fsystem::path, size>& filenames)
        {
            fsystem::path metafile_path(root_path/"benchmarks.txt");
            std::ofstream metafile(metafile_path.string());
            if (!metafile.good())
            {
                throw std::runtime_error("couldn't create metafile");
            }

            metafile << m_title << '\n' << m_x_label << '\n' << m_y_label << '\n';

            for (const auto& fname: filenames)
            {
                metafile << fname.string() << '\n';
            }
        }

        /*
        put ForwardIterator, not InputIterator, because technically
        the function is called in a loop with the same
        iterators, thus one might get confused
        if the loop is wrong or name is wrong
        */
        template <typename TimeUnit,
                typename InputDataForwardIterator,
                typename TimingsForwardIterator>
        void create_bench_file(const fsystem::path& p, std::size_t index,
                               InputDataForwardIterator input_first, InputDataForwardIterator input_last,
                               TimingsForwardIterator timings_first, TimingsForwardIterator timings_last)
        {
            //probably path overload is not in std yet
            std::ofstream bench_file(p.string());

            if (!bench_file.is_open())
            {
                throw std::runtime_error("couldn't create benchmark file " + p.string());
            }

            bench_file << p.stem().string() << '\n';

            while (input_first != input_last &&
                    timings_first != timings_last)
            {
                auto converted_time = std::chrono::duration_cast<TimeUnit>((*timings_first++)[index]);
                //                                                          ^^ since *timings is array
                //                                                          and [i] gives the needed timing
                bench_file << *input_first++ << ' ' << converted_time.count() << '\n';
            }

            const char* common_message_part = "Probably something is malfunctioning.";

            if (input_first != input_last)
            {
                std::cerr << "Input count exceeds timings count. " << common_message_part << '\n';
            }

            if (timings_first != timings_last)
            {
                std::cerr << "Timings count exceeds input count. " << common_message_part << '\n';
            }
        }
    };
}

#endif //AREA51_DEF_FORMATTER_HPP
