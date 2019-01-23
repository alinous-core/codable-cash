/*
 * memory.cpp
 *
 *  Created on: 2018/04/19
 *      Author: iizuka
 */


#include "debug/debugMacros.h"

#include "osenv/memory.h"

namespace alinous {


void* Mem::memset(void *__s, int __c, size_t __n) noexcept {
	return ::memset(__s, __c, __n);
}
void* Mem::memcpy(void *__restrict __dest, const void *__restrict __src, size_t __n) noexcept {
	return ::memcpy(__dest, __src, __n);
}
size_t Mem::strlen (const char *__s) noexcept {
	return ::strlen(__s);
}

wchar_t Mem::toupper (int ch) noexcept {
	return ::toupper(ch);
}

int Mem::wcscmp(const wchar_t *__s1, const wchar_t *__s2) noexcept {
	return ::wcscmp(__s1, __s2);
}

int alinous::Mem::wstrlen(const wchar_t* __s1) noexcept {
	return ::wcslen(__s1);
}

int Mem::strcmp(const char *__s1, const char *__s2) noexcept {
	return ::strcmp(__s1, __s2);
}

int Mem::memcmp(const void* lhs, const void* rhs, size_t count) {
	return ::memcmp(lhs, rhs, count);
}


} /* namespace alinous */

