#include "../src/algorithm.hpp"
#include "../src/random_engine.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

struct integer
{
    int x;
    integer(int y):
            x(y)
    {}

    integer(const integer& other) = delete; //non copyable
    integer& operator=(const integer& other) = delete;
};

bool operator<(const integer& lhs, const integer& rhs)
{
    return lhs.x < rhs.x;
}

std::ostream& operator<<(std::ostream& os, const integer& x)
{
    return os << x.x;
}

std::vector<int> generate_randomized_vector(std::size_t size)
{
    std::vector<int> v(size);

    static shino::random_int_generator<> gen(0, 100'000);
    gen(v.begin(), v.end());
    return v;
}

int main()
{
    int arr[] = {1, 2, 3, 4 , 5, 1};
    auto answer = most_frequent(std::begin(arr), std::end(arr));
    std::cout << "The most frequent integer is " <<
              *answer.first << " which occured " <<
              answer.second << " times\n";

    std::string names[] = {"Olzhas", "Erasyl", "Aigerym", "Akbota", "Akbota", "Erasyl", "Olzhas", "Olzhas"};
    auto most_frequent_name = most_frequent(std::begin(names), std::end(names));
    std::cout << "The most frequent name is " <<
              *most_frequent_name.first << " which occured " <<
              most_frequent_name.second << " times\n";

    integer weird_integers[] = {0, 1, 2, 3, 4, 5, 6, 1};
    auto most_frequent_integer = most_frequent(std::begin(weird_integers), std::end(weird_integers));
    std::cout << "The most frequent weird integer is " <<
              *most_frequent_integer.first << " which occured " <<
              most_frequent_integer.second << " times\n";


    auto input = generate_randomized_vector(1'000'000);
    auto start = std::chrono::high_resolution_clock::now();
    auto output = most_frequent(input.begin(), input.end());
    auto end = std::chrono::high_resolution_clock::now();



    std::cout << "The most frequent integer in 100'000 elements is " <<
              *output.first << " and it took " <<
              std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds to find it";
}

