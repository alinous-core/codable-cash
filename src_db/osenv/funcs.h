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

#include <stdlib.h>



namespace alinous {

#define S_PRINTF swprintf

#ifdef _WIN64
#define PATH_SEPARATOR L"\\"
#elseif _WIN32
#define PATH_SEPARATOR L"\\"
#else
#define PATH_SEPARATOR L"/"
#endif

class UnicodeString;

class Os {
public:
	static void* memcpy(void *__restrict __dest, const void *__restrict __src, size_t __n) noexcept;
	static size_t strlen (const char *__s) noexcept;
	static wchar_t toupper (int ch) noexcept;
	static int wcscmp(const wchar_t *__s1, const wchar_t *__s2) noexcept;

	/**************************************************************************
	 * File functions
	 */
	static char* realpath(const char *path, char *resolved_path) noexcept;
	static void realpath_free(char* path) noexcept;
	static bool file_exists(UnicodeString* path) noexcept;
	static int mkdirs(UnicodeString *path,
			bool __S_IRUSR , bool __S_IWUSR, bool __S_IXUSR,
			bool __S_IRGRP , bool __S_IWGRP, bool __S_IXGRP,
			bool __S_IROTH , bool __S_IWOTH, bool __S_IXOTH) noexcept;
};

}

#endif /* OSENV_FUNCS_H_ */
