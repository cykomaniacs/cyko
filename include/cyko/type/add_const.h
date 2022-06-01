#ifndef CYKO_TYPE_ADD_CONST_H
#define CYKO_TYPE_ADD_CONST_H

namespace cyko {
namespace type {
namespace internal
{

	template <typename T>
		struct add_const_impl
		{
			using result = T const;
		};

} // namespace cyko::type::internal

	template <typename T>
		using add_const = typename internal::add_const_impl<T>::result;

} // namespace cyko::type
} // namespace cyko

#endif
