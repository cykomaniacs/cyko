#ifndef CYKO_TYPE_CONJUNCTION_H
#define CYKO_TYPE_CONJUNCTION_H

#include <cyko/meta/och.h>
#include <cyko/type/conditional.h>

namespace cyko {
namespace type {
namespace internal
{

  template <typename...>
    struct conjunction_impl;

  template <typename T, typename... Tail>
    struct conjunction_impl<T, Tail...>
    : meta::conditional<T, conjunction_impl<meta::expression<decltype(Tail::value), Tail::value>...>, T>
    { };

  template <typename T>
    struct conjunction_impl<T>
    : T //meta::expression<decltype(T::value), T::value>
    { };

  template <>
    struct conjunction_impl<>
    : meta::bool_t<true>
    { };

} // namespace cyko::type::internal

  /**
   * @brief Inherits the first false type, or the last type if none are false.
   */

  template <typename... T>
    struct conjunction
    : internal::conjunction_impl<T...>
    {
      using self = conjunction<T...>;
    };

} // namespace cyko::type
} // namespace cyko

#ifdef CYKO_DEBUG
namespace debug
{
  using namespace cyko;
  using namespace cyko::type;

  static constexpr auto ccc = conjunction<
    meta::expression<int, 4>,
    meta::expression<short, 3>,
    meta::expression<long, 2>,
    meta::expression<long long, 1>
  >::value;
  static constexpr auto ddd = conjunction<
    meta::expression<int, 4>,
    meta::expression<short, 3>,
    meta::expression<long, 2>
  >::value;
  static constexpr auto eee = conjunction<
    meta::expression<int, 4>,
    meta::bool_t<false>,
    meta::expression<long, 3>
  >::value;
  static constexpr auto fff = conjunction<
    meta::expression<int, 4>
  >::value;
  static constexpr auto ffg = conjunction<
  >::value;
}
#endif

#endif
