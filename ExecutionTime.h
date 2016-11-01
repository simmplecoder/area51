#pragma once

#include <chrono>
#include <utility>

template <class Func, class ... Args>
std::chrono::duration<double> measure(Func function, Args&& ... args)
{
	auto start = std::chrono::high_resolution_clock::now();
	function(std::forward<Args>(args)...);
	auto end = std::chrono::high_resolution_clock::now();

	return end - start;
}
