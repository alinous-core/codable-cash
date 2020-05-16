/*
 * DatabaseException.h
 *
 *  Created on: 2020/05/12
 *      Author: iizuka
 */

#ifndef ENGINE_CDBEXCEPTION_H_
#define ENGINE_CDBEXCEPTION_H_

#include "base/Exception.h"

namespace codablecash {
class AbstractTransactionLog;

using namespace alinous;

class CdbException : public Exception {
public:
	CdbException(const char* srcfile, int srcline) noexcept;
	CdbException(Exception* cause, const char* srcfile, int srcline) noexcept;
	CdbException(const wchar_t* message, const char* srcfile, int srcline) noexcept;
	CdbException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept;
	virtual ~CdbException();

	void setCmd(AbstractTransactionLog* cmd) noexcept {
		this->cmd = cmd;
	}

	static const wchar_t* defaultMessage;


private:
	AbstractTransactionLog* cmd;
};

} /* namespace codablecash */

#endif /* ENGINE_CDBEXCEPTION_H_ */
