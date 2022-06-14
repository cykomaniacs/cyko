#ifndef CYKO_COMMON_TYPES_H
#define CYKO_COMMON_TYPES_H

#include <cstddef> // std::(nullptr_t | ptrdiff_t)
#include <cstdint> // std::(*int#*_t)

namespace cyko
{
  /**
   * @brief Basics
   *
   * - @b bool_t @e bool
   * - @b char_t @e char
   * - @b void_t @e void
   * - @b null_t @e std::nullptr_t
   */

	using bool_t = bool;
	using char_t = char;
	using void_t = void;

  /**
   * @brief Integers
   *
   * - @b short_t @e word / 2
   * - @b int_t   @e word
   * - @b long_t  @e word * 2
   *
   * @e word The optimal number of bits the processor handles as a unit.
   */

  #ifdef CYKO_BUILD_X64
  using short_t = ::std::int32_t;
  using   int_t = ::std::int64_t;
  using  long_t = ::std::int64_t;
  #elif  CYKO_BUILD_X86
  using short_t = ::std::int16_t;
  using   int_t = ::std::int32_t;
  using  long_t = ::std::int64_t;
  #endif

  /**
   * @brief Integers : sizes
   *
   * - @b int8_t  : @e 1 byte @e  8 bit
   * - @b int16_t : @e 2 byte @e 16 bit
   * - @b int32_t : @e 4 byte @e 32 bit
   * - @b int64_t : @e 8 byte @e 64 bit
   */

  using  int8_t = ::std ::int8_t;
  using int16_t = ::std::int16_t;
  using int32_t = ::std::int32_t;
  using int64_t = ::std::int64_t;

  /**
   * @brief Extensions
   *
   * - @b size_t @e std::size_t
   * - @b diff_t @e std::ptrdiff_t
   * - @b null_t @e std::nullptr_t
   */

  using size_t = decltype(sizeof(int));
  using diff_t = decltype(INTMAX_MAX);
  using null_t = decltype(nullptr);

  /**
   * @brief Extensions : Units
   *
   * - @b byte_t : @e byte (8 bits)
   * - @b word_t : @e word (optimal number-of-bits / size handled by the proc)
   */

  using byte_t = ::std ::int8_t; /** @b 1 byte @e  8 bit */
  #ifdef CYKO_BUILD_X64
  using word_t = ::std::int64_t; /** @b 8 byte @e 64 bit */
  #elif  CYKO_BUILD_X86
  using word_t = ::std::int32_t; /** @b 4 byte @e 32 bit */
  #endif



}

#ifdef CYKO_DEBUG
namespace debug
{
  using namespace cyko;

  enum SIZE
  {
     BYTE = 1, /** @b 1 byte @e  8 bit @b architecture-independent */
    #ifdef CYKO_BUILD_X64
    HWORD = 4, /** @b 4 byte @e 32 bit @b x64 */
     WORD = 8, /** @b 8 byte @e 64 bit @b x64 */
    DWORD = 8, /** @b 8 byte @e 64 bit @b x64 */
    #elif  CYKO_BUILD_X86
    HWORD = 2, /** @b 2 byte @e 16 bit @b x86 */
     WORD = 4, /** @b 4 byte @e 32 bit @b x86 */
    DWORD = 8, /** @b 8 byte @e 64 bit @b x86 */
    #endif
  };

  /// @test @b size @e standard:relationships
  static_assert(sizeof(  char_t ) <= sizeof( short_t ));
  static_assert(sizeof( short_t ) <= sizeof(   int_t ));
  static_assert(sizeof(   int_t ) <= sizeof(  long_t ));

  /// @test @b size @e basics
  static_assert(sizeof(  bool_t ) == sizeof( bool ));
  static_assert(sizeof(  char_t ) == sizeof( char ));

  /// @test @b size @e integers
  static_assert(sizeof( short_t ) == SIZE::HWORD);
  static_assert(sizeof(   int_t ) == SIZE::WORD);
  static_assert(sizeof(  long_t ) == SIZE::DWORD);
  /// @test @b size @e integers:sizes
  static_assert(sizeof(  int8_t ) == 1); /** @b 1 byte @e  8 bit */
  static_assert(sizeof( int16_t ) == 2); /** @b 2 byte @e 16 bit */
  static_assert(sizeof( int32_t ) == 4); /** @b 4 byte @e 32 bit */
  static_assert(sizeof( int64_t ) == 8); /** @b 8 byte @e 64 bit */

  /// @test @b size @e extensions
  static_assert(sizeof(  diff_t ) >= sizeof( decltype(INTMAX_MAX) ));
  /// @test @b size @e extensions:null
  /// NOLINTBEGIN(*nullptr*)
  static_assert(sizeof(  null_t ) == sizeof( ::std::nullptr_t ));
  static_assert(sizeof(  null_t ) >= sizeof( nullptr ));
  static_assert(sizeof(  null_t ) >= sizeof( NULL ));
  static_assert(sizeof(  null_t ) >= sizeof( static_cast<void*>(0) ));
  /// NOLINTEND(*nullptr*)
  /// @test @b size @e extensions:units
  static_assert(sizeof(  byte_t ) == SIZE::BYTE);
  static_assert(sizeof(  word_t ) == SIZE::WORD);
}
#endif

#endif
