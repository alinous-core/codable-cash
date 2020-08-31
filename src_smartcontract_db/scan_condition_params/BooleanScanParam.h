/*
 * BooleanScanParam.h
 *
 *  Created on: 2020/07/27
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_PARAMS_BOOLEANSCANPARAM_H_
#define SCAN_CONDITION_PARAMS_BOOLEANSCANPARAM_H_

namespace alinous {
class UnicodeString;
}
using namespace alinous;

#include "scan_condition_params/AbstractScanConditionParameter.h"

namespace codablecash {

class BooleanScanParam : public AbstractScanConditionParameter {
public:
	static const UnicodeString TRUE;
	static const UnicodeString FALSE;

	BooleanScanParam(const BooleanScanParam& inst);
	explicit BooleanScanParam(bool value);
	virtual ~BooleanScanParam();

	virtual const UnicodeString* toStringCode() noexcept;
	virtual AbstractScanConditionParameter* clone() const noexcept;

private:
	bool value;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_PARAMS_BOOLEANSCANPARAM_H_ */
