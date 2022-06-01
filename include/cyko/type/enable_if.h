#ifndef CYKO_TYPE_ENABLE_IF_H
#define CYKO_TYPE_ENABLE_IF_H

namespace cyko {
namespace type {
namespace internal
{

  template <cyko::bool_t, typename>
    struct enable_if_impl;

  template <typename T>
    struct enable_if_impl<false, T>
    { };

  template <typename T>
    struct enable_if_impl<true,  T>
    {
      using result = T;
    };

} // namespace cyko::type::internal

  /**
   * @brief Defines a type if the conditional value is true.
   * @details Defines a type if, and only if, the conditional value is true.
   * @tparam C The constant value.
   * @tparam A The result type.
   */

  template <cyko::bool_t C, typename T>
    using enable_if = typename internal::enable_if_impl<C, T>::result;

} // namespace cyko::type
} // namespace cyko

#endif

  /*
  // Primary template.
  /// Define a member typedef `type` only if a boolean constant is true.
  template<bool, typename _Tp = void>
    struct enable_if
    { };

  // Partial specialization for true.
  template<typename _Tp>
    struct enable_if<true, _Tp>
    { typedef _Tp type; };
  */
