//
// Created by olzhas on 2/18/17.
//

#include "../src/transform_iterator.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

void convert_strings_to_ints()
{
    std::vector<std::string> v{"23", "25", "27"}; //just random numbers
    std::vector<int> output(v.size());

    auto string_to_int = [](const std::string& x)
    {
        return std::stoi(x);
    };

    shino::transform_iterator<decltype(string_to_int),
            std::string, std::vector<int>::iterator> conversion_iterator(string_to_int, output.begin());

    std::copy(v.begin(), v.end(), conversion_iterator);

    std::cout << "Output after converting v to vector of ints\n";

    for (const auto& element: output)
    {
        std::cout << element << '\n';
    }
}

int main()
{
    convert_strings_to_ints();
}

