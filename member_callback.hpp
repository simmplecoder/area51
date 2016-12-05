#pragma once
#include <memory>
#include <utility>

template <typename T, typename Func>
class member_callback;

template <typename T, typename R, typename ... ArgTypes>
class member_callback<T, R(ArgTypes...)>
{
	std::shared_ptr<T> object;
	R(T::* callback)(ArgTypes ...);
public:
    using function_pointer = R(T::*)(ArgTypes ...);

	member_callback(const std::shared_ptr<T>& ptr, R(T::* function)(ArgTypes...)) :
		object(ptr),
		callback(function)
	{}

	member_callback(std::shared_ptr<T>&& ptr, R(T::* function)(ArgTypes...)) :
		object(std::move(ptr)),
		callback(function)
	{}

	R operator()(ArgTypes&& ... args)
	{
		return ((*object).*callback)(std::forward<ArgTypes>(args)...);
	}

	std::shared_ptr<T> get()
	{
		return object;
	}

    function_pointer get_function()
	{
		return callback;
	}
};