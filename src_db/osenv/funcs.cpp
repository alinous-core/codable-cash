/*
 * funcs.cpp
 *
 *  Created on: 2018/04/18
 *      Author: iizuka
 */


#include "funcs.h"

#include <sys/stat.h>

#include "base/UnicodeString.h"

namespace alinous {

void* Os::memcpy(void *__restrict __dest, const void *__restrict __src, size_t __n) noexcept {
	return ::memcpy(__dest, __src, __n);
}
size_t Os::strlen (const char *__s) noexcept {
	return ::strlen(__s);
}

wchar_t Os::toupper (int ch) noexcept {
	return ::toupper(ch);
}

int Os::wcscmp(const wchar_t *__s1, const wchar_t *__s2) noexcept {
	return ::wcscmp(__s1, __s2);
}

/**************************************************************************
 * File functions
 */
char* Os::realpath(const char *path, char *resolved_path) noexcept {
	return ::realpath(path, resolved_path);
}
void Os::realpath_free(char* path) noexcept {
	::free(path);
}

bool Os::file_exists(UnicodeString* path) noexcept {
	struct stat  st;
	const char* src = path->toCString();

	int ret = stat(src, &st);

	delete [] src;

	return ret == 0;
}

int Os::mkdirs(UnicodeString *path,
			bool __S_IRUSR , bool __S_IWUSR, bool __S_IXUSR,
			bool __S_IRGRP , bool __S_IWGRP, bool __S_IXGRP,
			bool __S_IROTH , bool __S_IWOTH, bool __S_IXOTH) noexcept {
	const char* dirPath = path->toCString();
	unsigned int mode = 0;

	if(__S_IRUSR){
		mode |= S_IRUSR;
	}
	if(__S_IWUSR){
		mode |= S_IWUSR;
	}
	if(__S_IXUSR){
		mode |= S_IXUSR;
	}

	if(__S_IRGRP){
		mode |= S_IRGRP;
	}
	if(__S_IWGRP){
		mode |= S_IWGRP;
	}
	if(__S_IXGRP){
		mode |= S_IXGRP;
	}

	if(__S_IROTH){
		mode |= S_IROTH;
	}
	if(__S_IWOTH){
		mode |= S_IWOTH;
	}
	if(__S_IXOTH){
		mode |= S_IXOTH;
	}

	int ret = ::mkdir(dirPath, mode);

	delete [] dirPath;

	return ret;
}

}
