#ifndef CYKO_COMMON_TYPES_H
#define CYKO_COMMON_TYPES_H

#include <cstddef>
#ifdef CYKO_BUILD_USE_STDINT
#include <cstdint>
#endif

namespace cyko
{

  /**
   * @brief Base types.
   *
   * @todo make cross-platform.
   * @todo make platform / architecture dependent.
   */

	using bool_t = bool;
	using char_t = char;

	using size_t = std::size_t;
	using void_t = void;

  /**
   * @brief The regular int type: cyko::int_t
   * @remarks 8 bytes(64 bits) on 64-bit systems.
   * @remarks 4 bytes(32 bits) on 32-bit systems.
   */

  #ifdef CYKO_BUILD_USE_STDINT
  #ifdef CYKO_BUILD_X64
  using  int_t = std::int64_t;
  #elif  CYKO_BUILD_X86
  using  int_t = std::int32_t;
  #endif
  #elif  CYKO_BUILD_CXX_MSVC
  #ifdef CYKO_BUILD_X64
  using  int_t = long long int;
  #elif  CYKO_BUILD_X86
  using  int_t = long int;
  #endif
  #elif  CYKO_BUILD_CXX_GCC
  #ifdef CYKO_BUILD_X64
  using  int_t = long long int;
  #elif  CYKO_BUILD_X86
  using  int_t = long int;
  #endif
  #elif  CYKO_BUILD_CXX_LLVM
  #ifdef CYKO_BUILD_X64
  using  int_t = long long int;
  #elif  CYKO_BUILD_X86
  using  int_t = long int;
  #endif
  #endif

  /**
   * @brief Types named by the size they refer to.
   * @remarks Each type is unsigned.
   * @code {.cpp}
   * cyko::byte_t  // 1 byte >  8 bit
   * cyko::word_t  // 2 byte > 16 bit
   * cyko::dword_t // 4 byte > 32 bit (double word)
   * cyko::qword_t // 8 byte > 64 bit (quad word)
   * @endcode
   */

  #ifdef CYKO_BUILD_USE_STDINT
  using  byte_t = std:: uint8_t;
  using  word_t = std::uint16_t;
  using dword_t = std::uint32_t;
  using qword_t = std::uint64_t;
  // std::[u]intptr_t;
  #else
  using  byte_t = unsigned char;
  using  word_t = unsigned short int;
  using dword_t = unsigned long  int;
  using qword_t = unsigned long long int;
  #endif

  /**
   * @brief The type of the null pointer literal @e cyko::null (nullptr).
   *
   * @details It is a distinct type that is not itself a @e pointer type or a
   * @e pointer-to-member type. Its values are null pointer constants (NULL),
   * and can be implicitly converted to any @e pointer and / or
   * @e pointer-to-member type.
   *
   * @remarks If two or more overloads accept different pointer types, an
   * overload for @e null_t is necessary to accept a null pointer argument.
   */

  using null_t = decltype(nullptr);
  using cull_t = decltype(NULL);

} // namespace cyko

#ifdef CYKO_DEBUG
namespace debug
{
  /// @test @b size @e integral

  /// @e standard default
  #ifdef CYKO_BUILD_X64
  static_assert(sizeof(::cyko  ::int_t) == 8); /** @b 8 byte @e 64 bit */
  #elif  CYKO_BUILD_X86
  static_assert(sizeof(::cyko  ::int_t) == 4); /** @b 4 byte @e 32 bit */
  #endif

  /// @e specials
  static_assert(sizeof(::cyko ::byte_t) == 1); /** @b 1 byte @e  8 bit */
  static_assert(sizeof(::cyko ::word_t) == 2); /** @b 2 byte @e 16 bit */
  static_assert(sizeof(::cyko::dword_t) == 4); /** @b 4 byte @e 32 bit */
  static_assert(sizeof(::cyko::qword_t) == 8); /** @b 8 byte @e 64 bit */
}
#endif

#endif
