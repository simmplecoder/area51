#include "fast_find.hpp"
#include "randomsequence.h"
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> v(10'000'000);
	random_int_generator<> gen(0, 10'000); //generate values in range
	gen(v.begin(), v.end());
	
	int n;
	std::cin >> n;
	auto it =find(v.begin(), v.end(), n);
	if (it != v.end())
	{
		std::cout << "Found it!\n" << *it << '\n';
	}
	else
	{
		std::cout << "Sadness\n";
	}
}
