#ifndef CYKO_TYPE_REMOVE_CONST_H
#define CYKO_TYPE_REMOVE_CONST_H

namespace cyko {
namespace type {
namespace internal
{

  template <typename T>
    struct remove_const_impl
    {
      using result = T;
    };

  template <typename T>
    struct remove_const_impl<T const>
    {
      using result = T;
    };

} // namespace cyko::type::internal

  /**
   * @brief Removes the @b const attribute from a type.
   * @remark Removes @e top-level attributes (see the example code).
   * @code {.cpp}
   * cyko::type::remove_const<int   const>   // int
   * cyko::type::remove_const<int   const&&> // int const&&
   * cyko::type::remove_const<int   const&>  // int const&
   * cyko::type::remove_const<int   const*>  // int const*
   * cyko::type::remove_const<int*  const>   // int*
   * cyko::type::remove_const<int&  const>   // int&
   * cyko::type::remove_const<int&& const>   // int&&
   * @endcode
   * @tparam T The type.
   */

  template <typename T>
    using remove_const = typename internal::remove_const_impl<T>::result;

} // namespace cyko::type
} // namespace cyko

#endif
