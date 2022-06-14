#ifndef CYKO_TYPE_SIZE_H
#define CYKO_TYPE_SIZE_H

#include <cyko/meta/expression.h>
#include <cyko/type/pack.h>

namespace cyko {
namespace type {
namespace internal
{

  /// @b impl @e decl

  template <typename... T>
    struct size_impl;

  /// @b impl @e spec

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

  /// @b help @e spec

  template <typename... Pack>
    struct size_help
    : size_impl<Pack...>
    { };

  template <typename... Pack>
    struct size_help<type::pack<Pack...>>
    : size_impl<Pack...>
    { };

} // namespace cyko::type::internal

  /**
   * @brief Size of a type (in bytes) or length of a type-pack.
   *
   * @see cyko::type::pack - Type list AKA type parameter-pack.
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
  using namespace ::cyko::type;

  /// @test @b none
  static_assert(size<>::equal<meta::size_t<0>>::value);

  /// @test @b type @e sizeof
  /// @test @b type @e sizeof
  static_assert(size< char          >::equal< meta::size_t<sizeof(char)>          >::value);
  static_assert(size< short int     >::equal< meta::size_t<sizeof(short int)>     >::value);
  static_assert(size< int           >::equal< meta::size_t<sizeof(int)>           >::value);
  static_assert(size< long  int     >::equal< meta::size_t<sizeof(long  int)>     >::value);
  static_assert(size< long long int >::equal< meta::size_t<sizeof(long long int)> >::value);
  static_assert(size< float         >::equal< meta::size_t<sizeof(float)>         >::value);
  static_assert(size< double        >::equal< meta::size_t<sizeof(double)>        >::value);
  static_assert(size< long double   >::equal< meta::size_t<sizeof(long double)>   >::value);
  static_assert(size< int[2]        >::equal< meta::size_t<sizeof(int[2])>        >::value);
  static_assert(size< int[2][3]     >::equal< meta::size_t<sizeof(int[2][3])>     >::value);
  static_assert(size< int[2][3][4]  >::equal< meta::size_t<sizeof(int[2][3][4])>  >::value);
  /// @test @b type @e sizeof @b meta::multiply
  static_assert(size< int[2]        >::equal< size<int>::multiply< meta::int_t<2>>                               >::value);
  static_assert(size< int[2][3]     >::equal< size<int>::multiply< meta::int_t<2>,meta::int_t<3>>                >::value);
  static_assert(size< int[2][3][4]  >::equal< size<int>::multiply< meta::int_t<2>,meta::int_t<3>,meta::int_t<4>> >::value);

  /// @test @b pack @e length
  static_assert(size< pack<>                          >::equal< meta::size_t<0> >::value);
  static_assert(size< pack<pack<>>                    >::equal< meta::size_t<1> >::value);
  static_assert(size< pack<void,char>                 >::equal< meta::size_t<2> >::value);
  static_assert(size< pack<void,char,int>             >::equal< meta::size_t<3> >::value);
  static_assert(size< pack<pack<void,char,int>,short> >::equal< meta::size_t<2> >::value);
  /// @test @b pack @e length equals @b size
  static_assert(size<                                 >::equal< pack<>::size                    >::value);
  static_assert(size< void,char                       >::equal< pack<void,char>::size           >::value);
  static_assert(size< void,char,int                   >::equal< pack<void,char,int>::size       >::value);
  static_assert(size< void,char,int,short             >::equal< pack<void,char,int,short>::size >::value);
}
#endif

#endif
