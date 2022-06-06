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

  template <typename... Args>
	  struct size_impl//<Args...>
	  : meta::size_t<sizeof...(Args)>
	  { };
  template <typename T>
		struct size_impl<T>
		: meta::size_t<sizeof(T)>
		{ };



  template <typename ...Args>
    struct size_help
    : size_impl<Args...>
    { };

  template <typename T>
    struct size_help<T>
    : type::conditional<type::is_array<T>, type::rank<T>, size_impl<T>>
    { };


} // namespace cyko::type::internal

/*
	template <typename...>
		struct list;

	template <typename T>
		struct size
		: meta::size_t<sizeof(T)>
		{ };

	template <typename... Args>
	  struct size<Args...>
	  : meta::size_t<sizeof...(Args)>
	  { };

	template <typename... Args>
		struct size<list<Args...>>
		: meta::size_t<sizeof...(Args)>
		{ };
*/

  template <typename... T>
    struct size
    : meta::size_t<internal::size_help<T...>::value>
    { };

  static constexpr cyko::size_t xd[] = {
    size<int>::value,
    size<char>::value,
    size<int, int>::value,
    size<int[]>::value,
    size<int[3][4]>::value,
    size<int[1][1][1][1]>::value,
    size<int[][6][4]>::value,
    size<int[5]>::value,
  };

} // namespace cyko::type
} // namespace cyko

#endif
