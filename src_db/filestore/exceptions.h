/*
 * exceptions.h
 *
 *  Created on: 2018/05/18
 *      Author: iizuka
 */

#ifndef FILESTORE_EXCEPTIONS_H_
#define FILESTORE_EXCEPTIONS_H_

#include "base/Exception.h"

namespace alinous {

class FileStorageException : public Exception{
public:
	FileStorageException(const char* srcfile, int srcline) noexcept;
	FileStorageException(Exception* cause, const char* srcfile, int srcline) noexcept;
	FileStorageException(const wchar_t* message, const char* srcfile, int srcline) noexcept;
	FileStorageException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept;
	virtual ~FileStorageException();
	static const wchar_t* defaultMessage;
};


} /* namespace alinous */

#endif /* FILESTORE_EXCEPTIONS_H_ */
