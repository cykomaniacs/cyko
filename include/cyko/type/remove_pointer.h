#ifndef CYKO_TYPE_REMOVE_POINTER_H
#define CYKO_TYPE_REMOVE_POINTER_H

#include <cyko/type/conditional.h>
#include <cyko/type/is_pointer.h>
#include <cyko/type/remove_cv.h>

namespace cyko {
namespace type {
namespace internal
{

  template <typename T>
    struct remove_pointer_base
    {
      using result = T;
    };


  template <typename T>
    struct remove_pointer_impl
    : remove_pointer_base<T>
    { };
  template <typename T>
    struct remove_pointer_impl<T*>
    : remove_pointer_base<T>
    { };
  template <typename T>
    struct remove_pointer_impl<T *const>
    : remove_pointer_base<T>
    { };
  template <typename T>
    struct remove_pointer_impl<T *volatile>
    : remove_pointer_base<T>
    { };
  template <typename T>
    struct remove_pointer_impl<T *const volatile>
    : remove_pointer_base<T>
    { };


  template <typename T>
    struct remove_pointer_loop
    : type::conditional<type::is_pointer<type::remove_cv<T>>,
      remove_pointer_loop<typename remove_pointer_impl<T>::result>,
      remove_pointer_base<T>>
    { };


  template <typename T, cyko::bool_t R>
    struct remove_pointer_help
    : type::conditional<meta::bool_t<R>,
      remove_pointer_loop<T>,
      remove_pointer_impl<T>>
    { };

} // namespace cyko::type::internal

  template <typename T, cyko::bool_t Recursive = false>
    using remove_pointer = typename internal::remove_pointer_help<T, Recursive>::result;

  /**
   * @brief Removes the @b pointer from a type.
   * @remark Keeps const / volatile attributes.
   * @code {.cpp}
   * cyko::type::remove_pointer<int const*> // int const
   * @endcode
   * @tparam T The type.
   * @tparam Recursive Remove all? = false
   *

  template <typename T, cyko::bool_t Recursive = false>
    using remove_pointer_bak = typename internal::remove_pointer_help<T, Recursive>::result;

  template <typename T, cyko::bool_t Recursive = false>
    using remove_pointer = typename internal::remove_pointer_core_recursive<T, meta::bool_t<Recursive>>::result;
  */

} // namespace cyko::type
} // namespace cyko

#endif
