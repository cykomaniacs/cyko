#ifndef CYKO_TYPE_PACK_H
#define CYKO_TYPE_PACK_H

#include <cyko/meta/decrease.h>
#include <cyko/meta/plus.h>
#include <cyko/meta/zero.h>
#include <cyko/type/none.h>

#include <cyko/meta/equal.h>
#include <cyko/meta/greater.h>
#include <cyko/meta/less.h>
#include <cyko/meta/eller.h>

namespace cyko {
namespace type {
namespace internal
{
  /// @b impl @e decl

  template <typename P, typename I, auto = meta::zero<I>::value>
    struct pick_impl;

  /// @b impl @e spec

  template <typename P, typename I>
    struct pick_impl<P, I, false>
    : pick_impl<typename P::tail, meta::decrease<I>>
    { };

  template <typename P, typename I>
    struct pick_impl<P, I, true>
    {
      using result = typename P::head;
    };

} // namespace cyko::type::internal

  /// @e ---- -
  /// @b pick
  /// @e ---- -

  template <typename P, cyko::size_t I>
    using pick = typename internal::pick_impl<P, meta::size_t<I>>::result;

  /// @e ---- -
  /// @b pack
  /// @e ---- -

  template <typename...>
    struct pack;

  template <typename Head, typename... Tail>
    struct pack<Head, Tail...>
    : pack<Tail...>
    {
      using self = pack<Head, Tail...>;
      using head = Head;
      using tail = pack<Tail...>;
      using size = meta::size_t<1>::template plus<typename tail::size>;

      template <cyko::size_t I> using pick = ::cyko::type::pick<self, I>;
    };

  template <>
    struct pack<>
    {
      using self = pack<>;
      using head = self;// element / item
      using tail = self;
      using size = meta::size_t<0>;

      template <cyko::size_t I> using pick = ::cyko::type::pick<self, I>;
    };

} // namespace cyko::type
} // namespace cyko


#ifdef CYKO_DEBUG
#include<cyko/type/is_same.h>
namespace debug
{
  using namespace ::cyko::type;

  /// @test @b pack @e size

  /// @e pack<[0]|[1]|[2]|[3]>
  static_assert(pack<              >::size::value == 0);
  static_assert(pack<char          >::size::value == 1);
  static_assert(pack<char,int      >::size::value == 2);
  static_assert(pack<char,int,short>::size::value == 3);

  /// @test @b pick

  /// @e pack<[0]>
  static_assert(is_same<pick<pack<>, 0>, pack<>>::value);
  static_assert(is_same<pick<pack<>, 0>, void>::negate::value);
  /// @e pack<[1]>
  static_assert(is_same<pick<pack<char>, 0>, char>::value);
  static_assert(is_same<pick<pack<char>, 0>, void>::negate::value);
  static_assert(is_same<pick<pack<char>, 1>, char>::negate::value);
  /// @e pack<[2]>
  static_assert(is_same<pick<pack<char,int>, 0>, char>::value);
  static_assert(is_same<pick<pack<char,int>, 1>, int >::value);
  static_assert(is_same<pick<pack<char,int>, 1>, void>::negate::value);
  static_assert(is_same<pick<pack<char,int>, 2>, char>::negate::value);
  static_assert(is_same<pick<pack<char,int>, 2>, int >::negate::value);
  /// @e pack<[3]>
  static_assert(is_same<pick<pack<char,int,short>, 0>, char >::value);
  static_assert(is_same<pick<pack<char,int,short>, 1>, int  >::value);
  static_assert(is_same<pick<pack<char,int,short>, 2>, short>::value);
  static_assert(is_same<pick<pack<char,int,short>, 2>, void >::negate::value);
  static_assert(is_same<pick<pack<char,int,short>, 3>, char >::negate::value);
  static_assert(is_same<pick<pack<char,int,short>, 3>, int  >::negate::value);
  static_assert(is_same<pick<pack<char,int,short>, 3>, short>::negate::value);

  /// @test @b pack @e pick

  /// @e pack<[0]>
  static_assert(is_same<pack<>::pick<0>, pack<>>::value);
  static_assert(is_same<pack<>::pick<0>, void>::negate::value);
  /// @e pack<[1]>
  static_assert(is_same<pack<char>::pick<0>, char>::value);
  static_assert(is_same<pack<char>::pick<0>, void>::negate::value);
  static_assert(is_same<pack<char>::pick<1>, char>::negate::value);
  /// @e pack<[2]>
  static_assert(is_same<pack<char,int>::pick<0>, char>::value);
  static_assert(is_same<pack<char,int>::pick<1>, int >::value);
  static_assert(is_same<pack<char,int>::pick<1>, void>::negate::value);
  static_assert(is_same<pack<char,int>::pick<2>, char>::negate::value);
  static_assert(is_same<pack<char,int>::pick<2>, int >::negate::value);
  /// @e pack<[3]>
  static_assert(is_same<pack<char,int,short>::pick<0>, char >::value);
  static_assert(is_same<pack<char,int,short>::pick<1>, int  >::value);
  static_assert(is_same<pack<char,int,short>::pick<2>, short>::value);
  static_assert(is_same<pack<char,int,short>::pick<2>, void >::negate::value);
  static_assert(is_same<pack<char,int,short>::pick<3>, char >::negate::value);
  static_assert(is_same<pack<char,int,short>::pick<3>, int  >::negate::value);
  static_assert(is_same<pack<char,int,short>::pick<3>, short>::negate::value);
}
#endif

#endif
