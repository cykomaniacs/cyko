#ifndef CYKO_META_MINUS_H
#define CYKO_META_MINUS_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace meta {
namespace internal
{

  /// @b base:expression

  template <typename T>
    struct minus_base
    : meta::expression<decltype(T::value), T::value>
    { };

  /// @b base:operator

  template <typename T, typename U>
    struct minus_tool
    : meta::expression<decltype(T::value - U::value), (T::value - U::value)>
    { };

  /// @b impl:specialization

  template <typename, typename...>
    struct minus_impl;

  template <typename T, typename U, typename Next, typename... Tail>
    struct minus_impl<T, U, Next, Tail...>
    : minus_impl<minus_tool<T, U>, Next, Tail...>
    { };

  template <typename T, typename U>
    struct minus_impl<T, U>
    : minus_tool<T, U>
    { };

  template <typename T>
    struct minus_impl<T>
    : minus_base<T>
    { };

} // namespace cyko::meta::internal

  template <typename T, typename... Tail>
    struct minus
    : meta::expression<decltype(internal::minus_impl<T, Tail...>::value),
                                internal::minus_impl<T, Tail...>::value>
    {
      using self = minus<T, Tail...>;
    };

} // namespace cyko::meta
} // namespace cyko

#ifdef CYKO_DEBUG
namespace debug
{
  using namespace cyko;

  static_assert(meta::minus<
    meta::int_t<2>
  >::value == 2);
  static_assert(meta::minus<
    meta::int_t<2>,
    meta::int_t<3>
  >::value == -1);
  static_assert(meta::minus<
    meta::int_t<2>,
    meta::int_t<3>,
    meta::int_t<2>
  >::value == -3);
  static_assert(meta::minus<
    meta::int_t<2>,
    meta::int_t<3>,
    meta::int_t<1>,
    meta::int_t<4>
  >::value == -6);
}
#endif

#endif
