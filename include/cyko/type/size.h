#ifndef CYKO_TYPE_SIZE_H
#define CYKO_TYPE_SIZE_H

#include <cyko/meta/expression.h>
//#include <cyko/meta/multiply.h>

#include <cyko/type/list.h>
//#include <cyko/type/rank.h>
//#include <cyko/type/is_array.h>
//#include <cyko/type/conditional.h>

namespace cyko {
namespace type {
namespace internal
{

  /// @b impl @e declaration

  template <typename...>
    struct size_impl;

  /// @b impl @e specialization

  template <typename T, typename U, typename... Pack>
    struct size_impl<T, U, Pack...>
	  : meta::size_t<2>::plus<meta::size_t<sizeof...(Pack)>>
	  { };

  template <typename T>
		struct size_impl<T>
		: meta::size_t<sizeof(T)>
		{ };

  template <>
		struct size_impl<>
		: meta::size_t<0>
		{ };

  /// @b help @e selector

  template <typename... Pack>
    struct size_help
    : size_impl<Pack...>
    { };

  template <typename... Pack>
    struct size_help<type::list<Pack...>>
    : size_impl<Pack...>
    { };

} // namespace cyko::type::internal

  /**
   * @brief Size of a type, type-pack, or type-list.
   *
   * @see cyko::type::list - Type list AKA type parameter-pack.
   */

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

  static_assert(size<>::equal<meta::size_t<0>>::value);
  /// @test @b type @e sizeof
  static_assert(size<char         >::equal<meta::size_t<sizeof(char)>>::value);
  static_assert(size<short int    >::equal<meta::size_t<sizeof(short int)>>::value);
  static_assert(size<int          >::equal<meta::size_t<sizeof(int)>>::value);
  static_assert(size<long int     >::equal<meta::size_t<sizeof(long int)>>());
  static_assert(size<long long int>::equal<meta::size_t<sizeof(long long int)>>::value);
  static_assert(size<float        >::equal<meta::size_t<sizeof(float)>>::value);
  static_assert(size<double       >::equal<meta::size_t<sizeof(double)>>::value);
  static_assert(size<long double  >::equal<meta::size_t<sizeof(long double)>>::value);
  /// @test @b type @e sizeof array
  static_assert(size<int[2]       >::equal< size<int>::multiply<meta::int_t<2>> >::value);
  static_assert(size<int[2][3]    >::equal< size<int>::multiply<meta::int_t<2>, meta::int_t<3>> >::value);
  static_assert(size<int[2][3][4] >::equal< size<int>::multiply<meta::int_t<2>, meta::int_t<3>, meta::int_t<4>> >::value);

  /// @test @b pack @e length
  static_assert(size<list<>                         >::equal<meta::size_t<0>>::value);
  static_assert(size<list<>                         >::equal<meta::size_t<0>>::value);
  static_assert(size<list<list<>>                   >::equal<meta::size_t<1>>::value);
  static_assert(size<list<void,char>                >::equal<meta::size_t<2>>::value);
  static_assert(size<list<void,char,int>            >::equal<meta::size_t<3>>::value);
  static_assert(size<list<list<void,char,int>,short>>::equal<meta::size_t<2>>::value);

  /// @test @b size @e and @b pack should be equal!
  static_assert(size<                   >::equal<list<>::size>::value);
  static_assert(size<void,char          >::equal<list<void,char>::size>::value);
  static_assert(size<void,char,int      >::equal<list<void,char,int>::size>::value);
  static_assert(size<void,char,int,short>::equal<list<void,char,int,short>::size>::value);
}
#endif

#endif
