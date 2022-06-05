﻿#ifndef CYKO_COMMON_TYPES_H
#define CYKO_COMMON_TYPES_H

#include <cstddef>
#ifdef CYKO_BUILD_USE_STDINT
#include <cstdint>
#endif

namespace cyko
{

	using  bool_t = bool;
	using  char_t = char;
  #ifdef CYKO_BUILD_USE_STDINT
  using    int_t = std::int64_t;
  #elif  CYKO_BUILD_TOOLSET_MSVC
  #ifdef CYKO_BUILD_X64
  using   int_t = long long int;          // 8 byte 64 bit
  #elif  CYKO_BUILD_X86
  using   int_t = long int;               // 4 byte 32 bit
  #endif
  #elif  CYKO_BUILD_TOOLSET_MSVCLANG
  #ifdef CYKO_BUILD_X64
  using   int_t = long long int;          // 8 byte 64 bit
  #elif  CYKO_BUILD_X86
  using   int_t = long int;               // 4 byte 32 bit
  #endif
  #elif  CYKO_BUILD_TOOLSET_GCC
  #ifdef CYKO_BUILD_X64
  using   int_t = long long int;          // 8 byte 64 bit
  #elif  CYKO_BUILD_X86
  using   int_t = long int;               // 4 byte 32 bit
  #endif
  #elif  CYKO_BUILD_TOOLSET_LLVM
  #ifdef CYKO_BUILD_X64
  using   int_t = long long int;          // 8 byte 64 bit
  #elif  CYKO_BUILD_X86
  using   int_t = long int;               // 4 byte 32 bit
  #endif
  #endif // CYKO_BUILD_USE_STDINT
	using  size_t = std::size_t;
	using  void_t = void;
	using  null_t = std::nullptr_t;

  /**
   * @todo make cross-platform.
   * @todo make platform / architecture dependent.
   */

  #ifdef CYKO_BUILD_USE_STDINT
  using  byte_t = std::uint8_t;
  using  word_t = std::uint16_t;
  using dword_t = std::uint32_t;
  using qword_t = std::uint64_t;
  // std::[u]intptr_t;
  #else
  using  byte_t = unsigned char;          // 1 byte  8 bit
  using  word_t = unsigned short int;     // 2 byte 16 bit
  using dword_t = unsigned long  int;     // 4 byte 32 bit
  using qword_t = unsigned long long int; // 8 byte 64 bit
  #endif

} // namespace cyko

#endif
