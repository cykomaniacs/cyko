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

  template <typename...>
    struct size_impl;

  template <typename T, typename... Pack>
    struct size_impl<T, Pack...>
	  : meta::size_t<1>::plus<meta::size_t<sizeof...(Pack)>>
	  { };

  template <typename T>
		struct size_impl<T>
		: meta::size_t<sizeof(T)>
		{ };

  template <>
		struct size_impl<>
		: meta::size_t<0>
		{ };

  /// @b help

  template <typename... Pack>
    struct size_help
    : size_impl<Pack...>
    { };

  template <typename... Pack>
    struct size_help<type::list<Pack...>>
    : size_impl<Pack...>
    { };
/*
  template <typename T>
    struct size_help<T>
    : type::conditional<type::is_array<T>, type::rank<T>, size_impl<T>>
    { };
*/
} // namespace cyko::type::internal

  /**
   * @brief The size of a single type, type parameter-pack, or type list.
   *
   * @see cyko::type::list - Simple list of types AKA type-parameter-pack.
   * @see cyko::type::rank - Number dimensions of an array type.
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

  static_assert(size<char>         ::equal<meta::size_t<sizeof(char)>>::value);
  static_assert(size<short int>    ::equal<meta::size_t<sizeof(short int)>>::value);
  static_assert(size<int>          ::equal<meta::size_t<sizeof(int)>>::value);
  static_assert(size<long int>     ::equal<meta::size_t<sizeof(long int)>>::value);
  static_assert(size<long long int>::equal<meta::size_t<sizeof(long long int)>>::value);
  static_assert(size<float>        ::equal<meta::size_t<sizeof(float)>>::value);
  static_assert(size<double>       ::equal<meta::size_t<sizeof(double)>>::value);
  static_assert(size<long double>  ::equal<meta::size_t<sizeof(long double)>>::value);

  /// @b list
  static_assert(size<list<>>                         ::equal<meta::size_t<0>>::value);
  static_assert(size<list<list<>>>                   ::equal<meta::size_t<1>>::value);
  static_assert(size<list<void,char>>                ::equal<meta::size_t<2>>::value);
  static_assert(size<list<void,char,int>>            ::equal<meta::size_t<3>>::value);
  static_assert(size<list<list<void,char,int>,short>>::equal<meta::size_t<2>>::value);
  /// @b size and @b list::size should be equal!
  static_assert(size<>                   ::equal<list<>::size>::value);
  static_assert(size<void,char>          ::equal<list<void,char>::size>::value);
  static_assert(size<void,char,int>      ::equal<list<void,char,int>::size>::value);
  static_assert(size<void,char,int,short>::equal<list<void,char,int,short>::size>::value);

  static constexpr auto a = sizeof(int[1]);
  static constexpr auto a = sizeof(int[2]);
  static constexpr auto a = sizeof(int[2][2]);
  static constexpr auto a = sizeof(int[1][2]);
  static constexpr auto b = meta::size_t<sizeof(int)>::multiply<meta::size_t<4>>::value;
  /// @b rank

  //static_assert(size<int[]>       ::equal<meta::size_t<1>>::value);
  //static_assert(size<int[][2]>    ::equ<meta::size_t<2>>::value);
  //static_assert(size<int[][1][2]> ::equal<meta::size_t<3>>::value);
  static_assert(size<int[2]>      ::equal< meta::multiply<size<int>,meta::int_t<2>> >::value);
  static_assert(size<int[2][3]>   ::equal< meta::multiply< meta::multiply<size<int>,meta::int_t<2>>, meta::int_t<3> > >::value);
  static_assert(size<int[2][3][4]>::equal<
    meta::multiply<
      meta::multiply<
        meta::multiply< size<int>, meta::int_t<2> >,
        meta::int_t<3>
    >,meta::int_t<4>
    > >::value
  );

  static_assert(size<int[2]>      ::equal< size<int>::times<meta::int_t<2>> >::value);
  static_assert(size<int[2][3]>   ::equal< size<int>::times<meta::int_t<2>>::times<meta::int_t<3>> >::value);
  static_assert(size<int[2][3][4]>::equal< size<int>::times<meta::int_t<2>>::times<meta::int_t<3>>::times<meta::int_t<4>> >::value);
}
#endif

#endif
