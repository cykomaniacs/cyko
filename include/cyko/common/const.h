#ifndef CYKO_COMMON_CONST_H
#define CYKO_COMMON_CONST_H

namespace cyko
{

  static constexpr auto null = nullptr;

}

#ifdef CYKO_DEBUG
namespace debug
{
  /// @test @b null @e data
  static_assert(::cyko::null == nullptr);
  /// @test @b null @e size
  static_assert(sizeof(::cyko::null) == sizeof(nullptr));
}
#endif

#endif
