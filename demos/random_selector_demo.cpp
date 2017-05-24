#include "../src/random_selector.hpp"
#include <string>
#include <iostream>

int main()
{
    random_selector<std::string> selector({"Marzhan", "David", "Jack", "Aisulu", "Darkhan"});

    for (int i = 0; i < 10; ++i)
    {
        std::cout << selector();
    }
}

