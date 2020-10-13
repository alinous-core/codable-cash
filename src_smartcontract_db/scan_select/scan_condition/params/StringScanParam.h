/*
 * StringScanParam.h
 *
 *  Created on: 2020/07/21
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_PARAMS_STRINGSCANPARAM_H_
#define SCAN_CONDITION_PARAMS_STRINGSCANPARAM_H_

#include "scan_select/scan_condition/params/AbstractScanConditionParameter.h"

namespace alinous {
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class StringScanParam : public AbstractScanConditionParameter {
public:
	StringScanParam(const StringScanParam& inst);
	StringScanParam(const UnicodeString* str);
	virtual ~StringScanParam();

	virtual const UnicodeString* toStringCode() noexcept;
	virtual IValueProvider* clone() const noexcept;

private:
	UnicodeString* value;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_PARAMS_STRINGSCANPARAM_H_ */
