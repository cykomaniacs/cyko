#ifndef CYKO_TYPE_SIZE_H
#define CYKO_TYPE_SIZE_H

#include <cyko/meta/expression.h>
#include <cyko/type/rank.h>
#include <cyko/type/is_array.h>
#include <cyko/type/conditional.h>

namespace cyko {
namespace type {
namespace internal
{

  template <typename... Pack>
	  struct size_impl
	  : meta::size_t<sizeof...(Pack)>
	  { };

  template <typename T>
		struct size_impl<T>
		: meta::size_t<sizeof(T)>
		{ };

  template <typename... Pack>
    struct size_help
    : size_impl<Pack...>
    { };

  template <typename T>
    struct size_help<T>
    : type::conditional<type::is_array<T>, type::rank<T>, size_impl<T>>
    { };


} // namespace cyko::type::internal

  template <typename... T>
    struct size
    : meta::size_t<internal::size_help<T...>::value>
    { };

} // namespace cyko::type
} // namespace cyko

#ifdef CYKO_DEBUG
namespace debug
{
  using namespace cyko::type;

  static_assert(size<char>::value          == sizeof(char));
  static_assert(size<short int>::value     == sizeof(short int));
  static_assert(size<int>::value           == sizeof(int));
  static_assert(size<long int>::value      == sizeof(long int));
  static_assert(size<long long int>::value == sizeof(long long int));
  static_assert(size<float>::value         == sizeof(float));
  static_assert(size<double>::value        == sizeof(double));
  static_assert(size<long double>::value   == sizeof(long double));

  static constexpr cyko::size_t x[] = {
    size<int>::value,
    size<char>::value,
    size<int, int>::value,
    size<int[]>::value,
    size<int[3][4]>::value,
    size<int[1][1][1][1]>::value,
    size<int[][6][4]>::value,
    size<int[5]>::value,
  };
}
#endif

#endif
