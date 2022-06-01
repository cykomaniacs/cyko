#ifndef CYKO_META_CONDITIONAL_H
#define CYKO_META_CONDITIONAL_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace meta {
namespace internal
{

  template <cyko::bool_t, typename T, typename F>
    struct conditional_help;

  template <typename T, typename F>
    struct conditional_help<false, T, F>
    : meta::expression<typename F::type, F::value>
    { };

  template <typename T, typename F>
    struct conditional_help<true,  T, F>
    : meta::expression<typename T::type, T::value>
    { };

} // namespace cyko::meta::internal

  /**
   * @brief Selects one of two values, depending on the specified condition.
   *
   * @tparam C The @anchor condition.
   * @tparam T The value ( @link cyko::meta::expression @endlink ) selected if the @ref condition is true.
   * @tparam F The value ( @link cyko::meta::expression @endlink ) selected if the @ref condition is false.
   */

  template <typename C, typename T, typename F>
    struct conditional
    : meta::expression<typename internal::conditional_help<C::value, T, F>::type, internal::conditional_help<C::value, T, F>::value>
    {
      using self = conditional<C, T, F>;
    };

} // namespace cyko::meta
} // namespace cyko

#endif
