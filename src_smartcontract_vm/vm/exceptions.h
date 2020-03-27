/*
 * exceptions.h
 *
 *  Created on: 2019/04/14
 *      Author: iizuka
 */

#ifndef VM_EXCEPTIONS_H_
#define VM_EXCEPTIONS_H_

#include "base/Exception.h"

namespace alinous {

class VmMemoryAllocationException : public Exception{
public:
	VmMemoryAllocationException(const char* srcfile, int srcline) noexcept;
	VmMemoryAllocationException(Exception* cause, const char* srcfile, int srcline) noexcept;
	VmMemoryAllocationException(const wchar_t* message, const char* srcfile, int srcline) noexcept;
	VmMemoryAllocationException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept;
	virtual ~VmMemoryAllocationException();
	static const wchar_t* defaultMessage;
};

class VmMethodNotFoundException : public Exception{
public:
	VmMethodNotFoundException(const char* srcfile, int srcline) noexcept;
	VmMethodNotFoundException(Exception* cause, const char* srcfile, int srcline) noexcept;
	VmMethodNotFoundException(const wchar_t* message, const char* srcfile, int srcline) noexcept;
	VmMethodNotFoundException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept;
	virtual ~VmMethodNotFoundException();
	static const wchar_t* defaultMessage;
};

} /* namespace alinous */

#endif /* VM_EXCEPTIONS_H_ */
