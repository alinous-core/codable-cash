/*
 * exceptions.h
 *
 *  Created on: 2018/11/11
 *      Author: iizuka
 */

#ifndef FILESTORE_BLOCK_EXCEPTIONS_H_
#define FILESTORE_BLOCK_EXCEPTIONS_H_

#include "base/Exception.h"

namespace alinous {


class BlockFileStorageException : public Exception{
public:
	BlockFileStorageException(const char* srcfile, int srcline) noexcept;
	BlockFileStorageException(Exception* cause, const char* srcfile, int srcline) noexcept;
	BlockFileStorageException(const wchar_t* message, const char* srcfile, int srcline) noexcept;
	BlockFileStorageException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept;
	virtual ~BlockFileStorageException();
	static const wchar_t* defaultMessage;
};

class BinaryFormatException : public Exception{
public:
	BinaryFormatException(const char* srcfile, int srcline) noexcept;
	BinaryFormatException(Exception* cause, const char* srcfile, int srcline) noexcept;
	BinaryFormatException(const wchar_t* message, const char* srcfile, int srcline) noexcept;
	BinaryFormatException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept;
	virtual ~BinaryFormatException();
	static const wchar_t* defaultMessage;
};

} /* namespace alinous */

#endif /* FILESTORE_BLOCK_EXCEPTIONS_H_ */
