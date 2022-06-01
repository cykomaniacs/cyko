#ifndef CYKO_TYPE_ADD_VOLATILE_H
#define CYKO_TYPE_ADD_VOLATILE_H

namespace cyko {
namespace type {
namespace internal
{

	template <typename T>
		struct add_volatile_impl
		{
			using result = T volatile;
		};

} // namespace cyko::type::internal

	template <typename T>
		using add_volatile = typename internal::add_volatile_impl<T>::result;

} // namespace cyko::type
} // namespace cyko

#endif
