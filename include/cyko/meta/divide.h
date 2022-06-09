#ifndef CYKO_META_DIVIDE_H
#define CYKO_META_DIVIDE_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace meta {
namespace internal
{

  /// @b base:expression

  template <typename T>
    struct divide_base
    : meta::expression<decltype(T::value), T::value>
    { };

  /// @b tool:operator

  template <typename T, typename U>
    struct divide_tool
    : meta::expression<decltype(T::value / U::value), (T::value / U::value)>
    { };

  /// @b impl:specialization

  template <typename, typename...>
    struct divide_impl;

  template <typename T, typename U, typename Next, typename... Tail>
    struct divide_impl<T, U, Next, Tail...>
    : divide_impl<divide_tool<T, U>, Next, Tail...>
    { };

  template <typename T, typename U>
    struct divide_impl<T, U>
    : divide_tool<T, U>
    { };

  template <typename T>
    struct divide_impl<T>
    : divide_base<T>
    { };

} // namespace cyko::meta::internal

  template <typename T, typename... Tail>
    struct divide
    : meta::expression<decltype(internal::divide_impl<T, Tail...>::value),
                                internal::divide_impl<T, Tail...>::value>
    {
      using self = divide<T, Tail...>;
    };

} // namespace cyko::meta
} // namespace cyko

#ifdef CYKO_DEBUG
namespace debug
{
  using namespace cyko;

  static_assert(meta::divide<
    meta::int_t<2>
  >::value == 2);
  static_assert(meta::divide<
    meta::int_t<2>,
    meta::int_t<3>
  >::value == 0);
  static_assert(meta::divide<
    meta::int_t<6>,
    meta::int_t<3>,
    meta::int_t<2>
  >::value == 1);
  static_assert(meta::divide<
    meta::int_t<9>,
    meta::int_t<3>,
    meta::int_t<1>,
    meta::int_t<2>
  >::value == 1);
  static_assert(meta::divide<
    meta::int_t<-4>,
    meta::int_t<-2>
  >::value == 2);
  static_assert(meta::divide<
    meta::int_t<-4>,
    meta::int_t<2>
  >::value == -2);
  static_assert(meta::divide<
    meta::int_t<6>,
    meta::int_t<-2>
  >::value == -3);
}
#endif

#endif
