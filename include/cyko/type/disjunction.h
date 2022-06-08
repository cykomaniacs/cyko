#ifndef CYKO_TYPE_DISJUNCTION_H
#define CYKO_TYPE_DISJUNCTION_H

#include <cyko/meta/expression.h>
#include <cyko/type/conditional.h>

namespace cyko {
namespace type {
namespace internal
{

  template <typename...>
    struct disjunction_impl;

  template <>
    struct disjunction_impl<>
    : meta::bool_t<false>
    { };

  template <typename T>
    struct disjunction_impl<T>
    : meta::expression<decltype(T::value), T::value>
    { };

  template <typename T, typename... Tail>
    struct disjunction_impl<T, Tail...>
    : meta::conditional<T, T, disjunction_impl<meta::expression<decltype(Tail::value), Tail::value>...>>
    { };

} // namespace cyko::type::internal

  /**
   * @brief Inherits the first true type, or the last type if none are false.
   */

  template <typename... T>
    struct disjunction_
    : meta::expression<decltype(internal::disjunction_impl<T...>::value),
                                internal::disjunction_impl<T...>::value>
    {
      using self = disjunction<T...>;
    };

  template <typename... T>
    using disjunction = typename internal::disjunction_impl<T...>::type;

} // namespace cyko::type
} // namespace cyko

#ifdef CYKO_DEBUG
namespace debug
{
  using namespace cyko;
  using namespace cyko::type;

  static constexpr auto ccc = disjunction<
    meta::expression<int, 4>,
    meta::expression<short, 3>,
    meta::expression<long, 2>,
    meta::expression<long long, 1>
  >::value;
  static constexpr auto ddd = disjunction<
    meta::expression<int, 4>,
    meta::expression<short, 3>,
    meta::expression<long, 2>
  >::value;
  static constexpr auto eee = disjunction<
    meta::expression<int, 0>,
    meta::bool_t<false>,
    meta::expression<long, 3>
  >::value;
  static constexpr auto fff = disjunction<
    meta::expression<int, 4>
  >::value;
  static constexpr auto ffg = disjunction<
  >::value;
}
#endif

#endif
