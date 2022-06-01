#ifndef CYKO_TYPE_REMOVE_VOLATILE_H
#define CYKO_TYPE_REMOVE_VOLATILE_H

namespace cyko {
namespace type {
namespace internal
{

  template <typename T>
    struct remove_volatile_impl
    {
      using result = T;
    };

  template <typename T>
    struct remove_volatile_impl<T volatile>
    {
      using result = T;
    };

} // namespace cyko::type::internal

  /**
   * @brief Removes the @b volatile attribute from a type.
   * @remark Removes @e top-level attributes (see the example code).
   * @code {.cpp}
   * cyko::type::remove_volatile<int   volatile>   // int
   * cyko::type::remove_volatile<int   volatile&&> // int volatile&&
   * cyko::type::remove_volatile<int   volatile&>  // int volatile&
   * cyko::type::remove_volatile<int   volatile*>  // int volatile*
   * cyko::type::remove_volatile<int*  volatile>   // int*
   * cyko::type::remove_volatile<int&  volatile>   // int&
   * cyko::type::remove_volatile<int&& volatile>   // int&&
   * @endcode
   * @tparam T The type.
   */

  template <typename T>
    using remove_volatile = typename internal::remove_volatile_impl<T>::result;

} // namespace cyko::type
} // namespace cyko

#endif
