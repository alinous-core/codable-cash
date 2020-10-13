/*
 * CdbValueCastException.h
 *
 *  Created on: 2020/09/22
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_VALUE_CDBVALUECASTEXCEPTION_H_
#define TABLE_RECORD_VALUE_CDBVALUECASTEXCEPTION_H_

#include "engine/CdbException.h"

namespace codablecash {

class CdbValueCastException: public CdbException {
public:
	CdbValueCastException(const char* srcfile, int srcline) noexcept;
	CdbValueCastException(Exception* cause, const char* srcfile, int srcline) noexcept;
	CdbValueCastException(const wchar_t* message, const char* srcfile, int srcline) noexcept;
	CdbValueCastException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept;

	virtual ~CdbValueCastException();
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_VALUE_CDBVALUECASTEXCEPTION_H_ */
