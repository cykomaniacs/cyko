#ifndef CYKO_COMMON_CONST_H
#define CYKO_COMMON_CONST_H

namespace cyko
{
  /** *** *
   * @brief The null pointer constant.
   */

  static constexpr ::cyko::null_t null = nullptr;

} // namespace cyko

#ifdef CYKO_DEBUG
namespace debug
{
  /// -----------------------------------------------------------------------
  /// @test @b null @e size
  /// -----------------------------------------------------------------------
  static_assert(sizeof(::cyko::null) == sizeof(nullptr));
}
#endif

#endif
