#include "../src/sort.hpp"
#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v{0, 8, 2, 4, -1};
    shino::shaker_sort(v.begin(), v.end());

    for (const auto& elem: v)
    {
        std::cout << elem << ' ';
    }
}

