/*
 * VmTransactionHandlerException.h
 *
 *  Created on: 2020/05/24
 *      Author: iizuka
 */

#ifndef VM_TRX_VMTRANSACTIONHANDLEREXCEPTION_H_
#define VM_TRX_VMTRANSACTIONHANDLEREXCEPTION_H_

#include "base/Exception.h"

namespace alinous {

class VmTransactionHandlerException : public Exception {
public:
	VmTransactionHandlerException(const char* srcfile, int srcline) noexcept;
	VmTransactionHandlerException(Exception* cause, const char* srcfile, int srcline) noexcept;
	VmTransactionHandlerException(const wchar_t* message, const char* srcfile, int srcline) noexcept;
	VmTransactionHandlerException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept;
	virtual ~VmTransactionHandlerException();
	static const wchar_t* defaultMessage;
};

} /* namespace alinous */

#endif /* VM_TRX_VMTRANSACTIONHANDLEREXCEPTION_H_ */
