export module meta;

#include <cyko/meta/expression.h>
#include <cyko/meta/conditional.h>
#include <cyko/meta/decrease.h>
#include <cyko/meta/divide.h>
#include <cyko/meta/eller.h>
#include <cyko/meta/equal.h>
#include <cyko/meta/increase.h>
#include <cyko/meta/minus.h>
#include <cyko/meta/multiply.h>
#include <cyko/meta/negate.h>
#include <cyko/meta/och.h>
#include <cyko/meta/plus.h>
#include <cyko/meta/zero.h>

export namespace meta
{
  /// @b arithmetic
  template <typename T, typename...Tail> using     plus = ::cyko::meta::plus<T, Tail...>;
  template <typename T, typename...Tail> using    minus = ::cyko::meta::minus<T, Tail...>;
  template <typename T, typename...Tail> using multiply = ::cyko::meta::multiply<T, Tail...>;
  template <typename T, typename...Tail> using   divide = ::cyko::meta::divide<T, Tail...>;

  /// @b logical / misc
  template <typename... T> using eller = ::cyko::meta::eller<T...>;
  template <typename... T> using   och = ::cyko::meta::och<T...>;

  template <typename C, typename T, typename F> using conditional = ::cyko::meta::conditional<C, T, F>;

  template <typename T, typename U> using   equal = ::cyko::meta::equal<T, U>;
  template <typename T>             using    zero = ::cyko::meta::zero<T>;
  template <typename T, typename U> using greater = ::cyko::meta::greater<T, U>;
  template <typename T, typename U> using    less = ::cyko::meta::less<T, U>;

  template <typename T> using increase = ::cyko::meta::increase<T>;
  template <typename T> using decrease = ::cyko::meta::decrease<T>;
  template <typename T> using   negate = ::cyko::meta::negate<T>;

  /// @b values
  template <typename T, T  V> using expression = ::cyko::meta::expression<T, V>;
  template <::cyko::bool_t V> using     bool_t = ::cyko::meta::bool_t<V>;
  template <::cyko::int_t  V> using      int_t = ::cyko::meta::int_t<V>;
  template <::cyko::size_t V> using     size_t = ::cyko::meta::size_t<V>;
}
