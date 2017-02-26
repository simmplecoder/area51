#ifndef SCOPE_EXIT_HPP
#define SCOPE_EXIT_HPP

#include <utility>

#define concat_impl(x, y) x##y
#define concat(x, y) concat_impl(x, y)

#define ANONYMOUS_VARIABLE(NAME) concat(NAME, __LINE__)

namespace detail
{
	template <typename Func>
	class scope_exit_guard
	{
		Func f;
	public:
		scope_exit_guard(Func&& f) :
			f(std::forward<Func>(f))
		{}

		~scope_exit_guard() noexcept(noexcept(f()))
		{
			f();
		}
	};

	struct dummy {};

	template <typename Func>
	scope_exit_guard<Func> operator+(dummy, Func&& f)
	{
		return std::forward<Func>(f);
	}
}

#define scope_exit \
	auto ANONYMOUS_VARIABLE(SCOPE_EXIT_WHATEVER) = detail::dummy{} + [&]()
#endif


