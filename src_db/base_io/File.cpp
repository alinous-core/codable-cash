/*
 * File.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#include <base_io/File.h>

#include "base/UnicodeString.h"

namespace alinous {

File::File(const UnicodeString* pathname) noexcept {
	this->path = new UnicodeString(pathname);
	this->pathSeparator = new UnicodeString(L"/");
}

File::~File() noexcept {
	delete this->path;
	delete this->pathSeparator;
}

} /* namespace alinous */
