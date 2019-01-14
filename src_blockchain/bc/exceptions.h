/*
 * exceptions.h
 *
 *  Created on: 2019/01/14
 *      Author: iizuka
 */

#ifndef BC_EXCEPTIONS_H_
#define BC_EXCEPTIONS_H_

#include "base/Exception.h"

namespace codablecash {
using namespace alinous;

class MulformattedTransactionBinaryException : public Exception{
public:
	MulformattedTransactionBinaryException(const char* srcfile, int srcline) noexcept;
	MulformattedTransactionBinaryException(Exception* cause, const char* srcfile, int srcline) noexcept;
	MulformattedTransactionBinaryException(const wchar_t* message, const char* srcfile, int srcline) noexcept;
	MulformattedTransactionBinaryException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept;
	virtual ~MulformattedTransactionBinaryException();
	static const wchar_t* defaultMessage;
};


} /* namespace codablecash */

#endif /* BC_EXCEPTIONS_H_ */
