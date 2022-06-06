#ifndef CYKO_TYPE_IS_FUNCTION_H
#define CYKO_TYPE_IS_FUNCTION_H

#include <cyko/meta/expression.h>
#include <cyko/meta/negate.h>
#include <cyko/meta/och.h>
#include <cyko/type/is_const.h>
#include <cyko/type/is_reference.h>

namespace cyko {
namespace type {
namespace internal
{
  template <typename...>
    struct conjunction_impl
    : meta::bool_t<true>
    { }; // If Traits is empty, true_type

  template <typename T, typename... Tail>
    struct conjunction_impl<T, Tail...>
    : meta::conditional<T, conjunction_impl<Tail...>, T>
    { static_assert(meta::is_expression<T>::value); }; // the first false trait in T, or the last trait if none are false

  template <typename T>
    struct conjunction_impl<T>
    : meta::expression<decltype(T::value), T::value>
    { static_assert(meta::is_expression<T>::value); }; // handle false trait or last trait


  static constexpr auto ccc = conjunction_impl<
    meta::expression<int, 4>,
    meta::expression<short, 3>,
    meta::expression<long, 1>,
    meta::expression<long long, false>>::value;
  static constexpr auto ddd = conjunction_impl<
    meta::expression<int, 4>,
    meta::expression<short, 3>,
    meta::expression<long, 2>>::value;
  static constexpr auto eee = conjunction_impl<
    meta::expression<int, 4>,
    meta::bool_t<false>,
    meta::expression<long, 3>>::value;
  static constexpr auto fff = conjunction_impl<
    meta::expression<int, 4>>::value;
  static constexpr auto ffg = conjunction_impl<>::value;

}

  template <typename... T>
    struct conjunction
    : internal::conjunction_impl<T...>
    {
      using self = conjunction<T...>;
    };

}
}

namespace cyko {
namespace type
{


  /**
   * @b only function and reference types @b can't be const qualified!
   */

  template <typename T>
    struct is_function
  //: meta::negate<type::is_const<T>>::template och<meta::negate<type::is_function<T>>>
    : meta::bool_t<meta::och<meta::negate<type::is_const<T>>, meta::negate<type::is_reference<T>>>::value>
  //: meta::och<!type::is_const<T>, !type::is_reference<T>>
    {
      using self = is_function<T>;
    };

} // namespace cyko::type
} // namespace cyko

#endif
