#ifndef CYKO_TYPE_IS_VOID_H
#define CYKO_TYPE_IS_VOID_H

#include <cyko/type/remove_cv.h>
#include <cyko/type/is_same.h>

namespace cyko {
namespace type
{

  /**
   * @brief Type is void?
   * @remark Ignores const / volatile qualifications.
   */

  template <typename T>
    struct is_void
    : type::is_same<type::remove_cv<T>, cyko::void_t>
    {
      using self = is_void<T>;
    };

} // namespace cyko::type
} // namespace cyko

#ifdef CYKO_DEBUG
namespace debug
{
  using namespace cyko::type;

  static_assert(is_void<cyko::void_t>::value);
  static_assert(is_void<void>::value);

  static_assert(is_void<void const>::value);
  static_assert(is_void<void volatile>::value);
  static_assert(is_void<void const volatile>::value);

  static_assert(is_void<void*>::negate::value);
  static_assert(is_void<void* const>::negate::value);
  static_assert(is_void<void* volatile>::negate::value);
  static_assert(is_void<void* const volatile>::negate::value);

  static_assert(is_void<void const*>::negate::value);
  static_assert(is_void<void const* const>::negate::value);
  static_assert(is_void<void const* volatile>::negate::value);
  static_assert(is_void<void const* const volatile>::negate::value);
}
#endif

#endif
