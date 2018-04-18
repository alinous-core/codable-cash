/*
 * funcs.h
 *
 *  Created on: 2018/04/18
 *      Author: iizuka
 */

#ifndef OSENV_FUNCS_H_
#define OSENV_FUNCS_H_

#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <ctype.h>

namespace alinous {

#define S_PRINTF swprintf


class Os {
public:
	static void* memcpy(void *__restrict __dest, const void *__restrict __src, size_t __n) noexcept {
		return ::memcpy(__dest, __src, __n);
	}
	static size_t strlen (const char *__s) noexcept {
		return ::strlen(__s);
	}

	static wchar_t toupper (int ch) noexcept {
		return ::toupper(ch);
	}

	static int wcscmp(const wchar_t *__s1, const wchar_t *__s2) noexcept {
		return ::wcscmp(__s1, __s2);
	}

};

}

#endif /* OSENV_FUNCS_H_ */
