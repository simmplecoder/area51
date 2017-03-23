#ifndef RANDOM_ENGINE_HPP
#define RANDOM_ENGINE_HPP

#include <random>

namespace shino {
    template<typename T = int, class Engine = std::random_device>
    class random_int_generator {
        Engine engine;
        std::uniform_int_distribution<T> dist;
    public:
        random_int_generator(T begin = 0, T end = std::numeric_limits<T>::max()) :
                dist(begin, end) {

        }

        template<typename OutputIt>
        void operator()(OutputIt first, OutputIt last) {
            while (first != last) {
                *first++ = dist(engine);
            }
        }

        T operator()() {
            return dist(engine);
        }
    };
}

#endif
