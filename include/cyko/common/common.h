#ifndef CYKO_COMMON_COMMON_H
#define CYKO_COMMON_COMMON_H

/**
 * @file common.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-06-10
 *
 * @copyright Copyright (c) 2022
 *
 * Immediately after the header file comment (and include guards if working on
 * a header file), the minimal list of #includes required by the file should
 * be listed. We prefer these #includes to be listed in this order:
 *
 * Main Module Header
 * Local/Private Headers
 * LLVM project/subproject headers (clang/..., lldb/..., llvm/..., etc)
 * System #includes
 *
 * and each category should be sorted lexicographically by the full path.
 * The Main Module Header file applies to .cpp files which implement an
 * interface defined by a .h file. This #include should always be included
 * first regardless of where it lives on the file system. By including a
 * header file first in the .cpp files that implement the interfaces,
 * we ensure that the header does not have any hidden dependencies which are
 * not explicitly #included in the header, but should be. It is also a form
 * of documentation in the .cpp file to indicate where the interfaces it
 * implements are defined.
 *
 * LLVM project and subproject headers should be grouped from most specific to
 * least specific, for the same reasons described above. For example,
 * LLDB depends on both clang and LLVM, and clang depends on LLVM.
 * So an LLDB source file should include lldb headers first, followed by clang
 * headers, followed by llvm headers, to reduce the possibility (for example)
 * of an LLDB header accidentally picking up a missing include due to the
 * previous inclusion of that header in the main source file or some earlier
 * header file. clang should similarly include its own headers before
 * including llvm headers. This rule applies to all LLVM subprojects.
 */

#include <cyko/common/types.h>
#include <cyko/common/const.h>

#include <cyko/module/meta.h>

#endif
