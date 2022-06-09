#ifndef CYKO_META_PLUS_H
#define CYKO_META_PLUS_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace meta {
namespace internal
{

  /// @b base:expression

  template <typename T>
    struct plus_base
    : meta::expression<decltype(T::value), T::value>
    { };

  /// @b base:operator

  template <typename T, typename U>
    struct plus_tool
    : meta::expression<decltype(T::value + U::value), (T::value + U::value)>
    { };

  /// @b impl:specialization

  template <typename, typename...>
    struct plus_impl;

  template <typename T, typename U, typename Next, typename... Tail>
    struct plus_impl<T, U, Next, Tail...>
    : plus_impl<plus_tool<T, U>, Next, Tail...>
    { };

  template <typename T, typename U>
    struct plus_impl<T, U>
    : plus_tool<T, U>
    { };

  template <typename T>
    struct plus_impl<T>
    : plus_base<T>
    { };

} // namespace cyko::meta::internal

  template <typename T, typename... Tail>
    struct plus
    : meta::expression<decltype(internal::plus_impl<T, Tail...>::value),
                                internal::plus_impl<T, Tail...>::value>
    {
      using self = plus<T, Tail...>;
    };

} // namespace cyko::meta
} // namespace cyko

#ifdef CYKO_DEBUG
namespace debug
{
  using namespace cyko;

  static_assert(meta::plus<
    meta::int_t<2>
  >::value == 2);
  static_assert(meta::plus<
    meta::int_t<2>,
    meta::int_t<3>
  >::value == 5);
  static_assert(meta::plus<
    meta::int_t<2>,
    meta::int_t<3>,
    meta::int_t<2>
  >::value == 7);
  static_assert(meta::plus<
    meta::int_t<2>,
    meta::int_t<3>,
    meta::int_t<1>,
    meta::int_t<4>
  >::value == 10);
}
#endif

#endif
