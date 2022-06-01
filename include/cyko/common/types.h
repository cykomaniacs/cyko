#ifndef CYKO_COMMON_TYPES_H
#define CYKO_COMMON_TYPES_H

#include <cstddef>

namespace cyko
{

	using  bool_t = bool;
	using  char_t = char;
  #ifdef CYKO_BUILD_TOOLCHAIN_MSVC
  #ifdef CYKO_BUILD_X64
  using   int_t = long long int;          // 8 byte 64 bit
  #elif  CYKO_BUILD_X32
  using   int_t = long int;               // 4 byte 32 bit
  #endif
  #elif  CYKO_BUILD_TOOLCHAIN_GCC
  #ifdef CYKO_BUILD_X64
  using   int_t = long long int;          // 8 byte 64 bit
  #elif  CYKO_BUILD_X32
  using   int_t = long int;               // 4 byte 32 bit
  #endif
  #elif  CYKO_BUILD_TOOLCHAIN_CLANG
  #ifdef CYKO_BUILD_X64
  using   int_t = long long int;          // 8 byte 64 bit
  #elif  CYKO_BUILD_X32
  using   int_t = long int;               // 4 byte 32 bit
  #endif
  #endif
	using  size_t = std::size_t;
	using  void_t = void;
	using  null_t = std::nullptr_t;

  using  byte_t = unsigned char;          // 1 byte  8 bit
  using  word_t = unsigned short int;     // 2 byte 16 bit
  using dword_t = unsigned long  int;     // 4 byte 32 bit
  using qword_t = unsigned long long int; // 8 byte 64 bit

} // namespace cyko

#endif
