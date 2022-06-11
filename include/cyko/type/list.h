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

#ifdef CYKO_DEBUG
#include<cyko/type/is_same.h>
namespace debug
{
  using namespace cyko;
  using namespace cyko::type;

  static_assert(cyko::type::list<
    char,
    int,
    short,
    long,
    float,
    double>::size::value == 6
  );
}
#endif

#endif
