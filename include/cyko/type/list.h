#ifndef CYKO_TYPE_LIST_H
#define CYKO_TYPE_LIST_H

#include <cyko/meta/decrease.h>
#include <cyko/meta/plus.h>
#include <cyko/meta/zero.h>

namespace cyko {
namespace type
{

  template <typename...>
    struct list;

  template <typename Head, typename... Tail>
    struct list<Head, Tail...>
    : list<Tail...>
    {
      using self = list<Head, Tail...>;
      using type = Head;
      using head = Head;
      using tail = list<Tail...>;
      using size = meta::size_t<1>::template plus<typename tail::size>;
    };

  template <>
    struct list<>
    {
      using self = list<>;
      using type = list<>;
      using head = list<>;
      using tail = list<>;
      using size = meta::size_t<0>;
    };

} // namespace cyko::type
} // namespace cyko


namespace cyko {
namespace type {
namespace internal
{

  template <typename L, typename I, cyko::bool_t = meta::zero<I>::value>
    struct element_impl;

  template <typename L, typename I>
    struct element_impl<L, I, false>
    : element_impl<typename L::tail, meta::decrease<I>>
    { };

  template <typename L, typename I>
    struct element_impl<L, I, true>
    {
      using result = typename L::head;
    };

} // namespace cyko::type::internal

  template <typename L, cyko::size_t I>
    using element = typename internal::element_impl<L, meta::size_t<I>>::result;

} // namespace cyko::type
} // namespace cyko

#endif
