#ifndef RANDOM_ENGINE_HPP
#define RANDOM_ENGINE_HPP

#include <random>
#include <memory>
#include <type_traits>
#include <utility>

template <typename T>
inline constexpr bool is_integer_type = std::is_integral_v<T>;

namespace shino
{
    template <typename IntegerType = int, typename RandomNumberEngine = std::mt19937_64>
    class random_int_generator
    {
        std::unique_ptr<RandomNumberEngine> engine;
        std::uniform_int_distribution<IntegerType> dist;
    public:
        template <typename ... Ts>
        random_int_generator(IntegerType first = 0,
                             IntegerType last = std::numeric_limits<IntegerType>::max(),
                             Ts&& ... args):
                engine(std::make_unique<RandomNumberEngine>(std::forward<Ts>(args)...)),
                dist(first, last)
        {}

        //allow move construction since it is disabled by deleted copy constructor
        random_int_generator(random_int_generator&& other) = default;

        void range(IntegerType first,
                   IntegerType last = std::numeric_limits<IntegerType>::max())
        {
            dist = std::uniform_int_distribution<IntegerType>(first, last);
        }

        std::pair<IntegerType, IntegerType>
        range()
        {
            return {dist.a(), dist.b()};
        };

        template <typename OutputIt>
        void operator()(OutputIt first, OutputIt last)
        {
            while (first != last)
            {
                *first++ = dist(*engine);
            }
        }

        IntegerType operator()()
        {
            return dist(*engine);
        }

        /*
         * Providing const versions doesn't make sense because
         * it is impossible to do anything meaningful with
         * const random int generator
         * */
        RandomNumberEngine& get_engine()
        {
            return *engine;
        }

        std::uniform_int_distribution<IntegerType>&
        get_distribution()
        {
            return dist;
        }
    };
}

#endif
