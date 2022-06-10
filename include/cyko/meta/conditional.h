#ifndef CYKO_META_CONDITIONAL_H
#define CYKO_META_CONDITIONAL_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace meta {
namespace internal
{

  /// @b help @e declaration

  template <typename C, typename, typename, auto = static_cast<cyko::bool_t>(C::value)>
    struct conditional_help;

  /// @b help @e specialization

  template <typename C, typename L, typename R>
    struct conditional_help<C, L, R, false>
    : meta::expression<decltype(R::value), R::value>
    { };

  template <typename C, typename L, typename R>
    struct conditional_help<C, L, R, true>
    : meta::expression<decltype(L::value), L::value>
    { };

} // namespace cyko::meta::internal

  /**
   * @brief The conditional / ternary operator.
   *
   * @tparam C The condition.
   * @tparam L @b L as in @e LHS. Selected if the @e condition is @e true.
   * @tparam R @b R as in @e RHS. Selected if the @e condition is @e false.
   */

  template <typename C, typename L, typename R>
    struct conditional
    : meta::expression<decltype(internal::conditional_help<C, L, R>::value),
                                internal::conditional_help<C, L, R>::value>
    {
      using self = conditional<C, L, R>;
    };

} // namespace cyko::meta
} // namespace cyko

#endif
