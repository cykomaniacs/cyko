#ifndef CYKO_TYPE_CONDITIONAL_H
#define CYKO_TYPE_CONDITIONAL_H

namespace cyko {
namespace type {
namespace internal
{

  template <cyko::bool_t, typename, typename>
		struct conditional_impl;

	template <typename T, typename F>
		struct conditional_impl<false, T, F>
		{
			using result = F;
		};

	template <typename T, typename F>
		struct conditional_impl<true,  T, F>
		{
			using result = T;
		};

} // namespace cyko::type::internal

	template <typename C, typename T, typename F>
		using conditional = typename internal::conditional_impl<C::value, T, F>::result;

} // namespace cyko::type
} // namespace cyko

#endif
