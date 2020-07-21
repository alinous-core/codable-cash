/*
 * StringScanParam.h
 *
 *  Created on: 2020/07/21
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_PARAMS_STRINGSCANPARAM_H_
#define SCAN_CONDITION_PARAMS_STRINGSCANPARAM_H_

#include "scan_condition_params/AbstractScanConditionParameter.h"

#include "scan_condition/IValueProvider.h"

namespace alinous {
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class StringScanParam : public AbstractScanConditionParameter, public IValueProvider {
public:
	StringScanParam(const UnicodeString* str);
	virtual ~StringScanParam();

private:
	UnicodeString* value;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_PARAMS_STRINGSCANPARAM_H_ */
