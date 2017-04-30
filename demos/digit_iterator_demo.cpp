#include "../src/input_digit_iterator.hpp"

#include <iostream>
#include <algorithm>
#include <vector>

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v)
{
    os << '[';
    if (v.empty())
    {
        os << ']';
        return os;
    }

    for (std::size_t i = 0; i < v.size() - 1; ++i)
    {
        os << v[i] << ' ';
    }

    os << v.back() << ']';
    return os;
}

void showcase_input(int num)
{
    shino::input_digit_iterator<int> first(num);
    shino::input_digit_iterator<int> last;

    std::cout << "number is " << num << '\n';
    std::cout << "Streaming num as iterator: ";
    std::copy(first, last, std::ostream_iterator<int>(std::cout));
    std::cout << '\n';

    std::cout << "Streaming number into vector: ";
    first = shino::input_digit_iterator<int>(num);
    std::vector<int> digits(first, last);
    std::cout << digits;
    std::cout << '\n';

    std::cout << "Reversing the vector: ";
    std::reverse(digits.begin(), digits.end());
    std::cout << digits;

    std::cout << "\n-----------\n\n";
}

int main()
{
    for (const auto& num: {123456, 0, 256})
    {
        showcase_input(num);
    }
}

