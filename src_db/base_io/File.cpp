/*
 * File.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#include "base_io/File.h"
#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "osenv/funcs.h"

namespace alinous {

const UnicodeString File::pathSeparator(PATH_SEPARATOR);

File::File(const UnicodeString* pathname) noexcept {
	this->path = new UnicodeString(pathname);
}

File::~File() noexcept {
	delete this->path;
}

UnicodeString* File::getAbsolutePath() const {
	if(isAbsolute()){
		return this->path;
	}

	UnicodeString* retPath = __getAbsolutePath();
	if(retPath != nullptr){
		return retPath;
	}


}

UnicodeString* File::__getAbsolutePath() const noexcept {
	const char* src = path->toCString();
	char* realp = Os::realpath(src, nullptr);

	delete [] src;

	if(realp == nullptr){
		return nullptr;
	}

	UnicodeString* ret = new UnicodeString(realp);

	Os::realpath_free(realp);

	return ret;
}

bool File::isAbsolute() const noexcept {
	return this->path->startsWith(&pathSeparator);
}

bool File::mkdirs() const noexcept {
	UnicodeString* src = getAbsolutePath();


}

} /* namespace alinous */
