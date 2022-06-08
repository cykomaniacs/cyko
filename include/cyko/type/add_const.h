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

 /**
   * @brief Adds a top-level @b const qualifier to a type.
   * @see The example code.
   * @code {.cpp}
   * cyko::type::remove_const<int>   // int vonst
   * cyko::type::remove_const<int&&> // int&& const
   * cyko::type::remove_const<int&>  // int& const
   * cyko::type::remove_const<int*>  // int* const
   * cyko::type::remove_const<int*  const>   // int*
   * cyko::type::remove_const<int&  const>   // int&
   * cyko::type::remove_const<int&& const>   // int&&
   * @endcode
   * @tparam T The type.
   */

	template <typename T>
		using add_const = typename internal::add_const_impl<T>::result;

} // namespace cyko::type
} // namespace cyko

#endif
