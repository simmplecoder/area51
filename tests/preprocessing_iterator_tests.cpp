//
// Created by olzhas on 2/18/17.
//

#include "../src/preprocessing_iterator.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

int f(const std::string&);

int main()
{
    std::vector<std::string> v{"23", "25", "27"};
    std::vector<int> output(3);

    auto string_to_int = [](const std::string& x)
    {
        return std::stoi(x);
    };

    shino::preprocessing_iterator<int(*)(const std::string&, std::size_t*, int),
            std::string, std::vector<int>::iterator> iterator(&std::stoi, output.begin());

    std::copy(v.begin(), v.end(), iterator);

    std::cout << "Output after converting v to vector of ints\n";

    for (const auto& element: output)
    {
        std::cout << element << '\n';
    }

//    auto multiplier = [](int x)
//    {
//        return x * 2;
//    };
//
//    preprocessing_iterator<decltype(multiplier),
//            int, std::vector<int>::iterator> it(multiplier, output.begin());
//
//    std::cout << "Enter three numbers";
//    std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), it);
//
//
//    std::cout << "multiplying by two";
//    for (const auto& element: output)
//    {
//        std::cout << element << '\n';
//    }
}