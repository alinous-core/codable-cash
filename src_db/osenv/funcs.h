/*
 * funcs.h
 *
 *  Created on: 2018/04/18
 *      Author: iizuka
 */

#ifndef OSENV_FUNCS_H_
#define OSENV_FUNCS_H_

#include "base/ArrayList.h"

#include <stdlib.h>
#include <pthread.h>

namespace alinous {



#ifdef _WIN64
#define PATH_SEPARATOR L"\\"
#elseif _WIN32
#define PATH_SEPARATOR L"\\"
#else
#define PATH_SEPARATOR L"/"
#endif

#define THREAD_ID pthread_t

class UnicodeString;


class Os {
public:
	/**************************************************************************
	 * Thread functions
	 */
	static THREAD_ID getCurrentThreadId() noexcept;
	static void setThreadName(THREAD_ID id, const char* name) noexcept;
	static UnicodeString* getThreadName(THREAD_ID id) noexcept;

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
	static int deleteFile(const UnicodeString *path) noexcept;
	static bool isDirectory(const UnicodeString* path) noexcept;
	static bool isFile(const UnicodeString* path) noexcept;
	static ArrayList<UnicodeString>* listFiles(const UnicodeString* path) noexcept;
};

}

#endif /* OSENV_FUNCS_H_ */
