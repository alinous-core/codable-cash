/*
 * memory.h
 *
 *  Created on: 2018/04/19
 *      Author: iizuka
 */

#ifndef OSENV_MEMORY_H_
#define OSENV_MEMORY_H_

#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <ctype.h>

#include <stdio.h>

namespace alinous {

#define S_PRINTF swprintf

class Mem {
public:
	static void* memcpy(void *__restrict __dest, const void *__restrict __src, size_t __n) noexcept;
	static void* memset(void *__s, int __c, size_t __n) noexcept;
	static int memcmp(const void* lhs, const void* rhs, size_t count);

	static size_t strlen (const char *__s) noexcept;
	static wchar_t toupper (int ch) noexcept;
	static int wcscmp(const wchar_t *__s1, const wchar_t *__s2) noexcept;
	static int wstrlen(const wchar_t *__s1) noexcept;

	static int strcmp(const char *__s1, const char *__s2) noexcept;
};

} /* namespace alinous */

#endif /* OSENV_MEMORY_H_ */
