#ifndef CYKO_META_MULTIPLY_H
#define CYKO_META_MULTIPLY_H

#include <cyko/meta/expression.h>
#include <cyko/type/conditional.h>
#include <cyko/meta/conditional.h>

namespace cyko {
namespace meta {
namespace internal
{

  template <typename T, typename U>
    struct multiply_tool
    : meta::expression<decltype(T::value * U::value), (T::value * U::value)>
    { };



  template <typename, typename...>
    struct multiply_impl;
/*
  template <typename T, typename U, typename... Tail>
    struct multiply_impl<T, U, Tail...>               // + 2 (T and U)
    : type::conditional<meta::bool_t<(((sizeof...(Tail)) + 2) > 2)>,
      multiply_impl<multiply_tool<T, U>, Tail...>,
      multiply_tool<T, U>>
    { };
*/
  template <typename T, typename U, typename Next, typename... Tail>
    struct multiply_impl<T, U, Next, Tail...>
    : multiply_impl<multiply_tool<T, U>, Next, Tail...>
    { };

  template <typename T, typename U>
    struct multiply_impl<T, U>
    : multiply_tool<T, U>
    { };

  template <typename T>
    struct multiply_impl<T>
    : meta::expression<decltype(T::value), T::value>
    { };

  static constexpr auto axa = multiply_impl<
    //meta::int_t<2>,
    meta::int_t<3>,
    meta::int_t<4>,
    meta::int_t<2>
  >::value;

} // namespace cyko::meta::internal

  template <typename T, typename... Tail>
    struct multiply
    : meta::expression<decltype(internal::multiply_impl<T, Tail...>::value),
                                internal::multiply_impl<T, Tail...>::value>
    {
      using self = multiply<T, Tail...>;
    };

} // namespace cyko::meta
} // namespace cyko

#ifdef CYKO_DEBUG
namespace debug
{
  using namespace cyko;

  static_assert(meta::multiply<
    meta::int_t<2>
  >::value == 2);
  static_assert(meta::multiply<
    meta::int_t<2>,
    meta::int_t<3>
  >::value == 6);
  static_assert(meta::multiply<
    meta::int_t<2>,
    meta::int_t<3>,
    meta::int_t<2>
  >::value == 12);
  static_assert(meta::multiply<
    meta::int_t<2>,
    meta::int_t<3>,
    meta::int_t<1>,
    meta::int_t<4>
  >::value == 24);
}
#endif

#endif
