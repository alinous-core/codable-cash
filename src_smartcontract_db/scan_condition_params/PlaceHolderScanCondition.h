/*
 * PlaceHolderScanCondition.h
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_PARAMS_PLACEHOLDERSCANCONDITION_H_
#define SCAN_CONDITION_PARAMS_PLACEHOLDERSCANCONDITION_H_

#include "scan_condition_params/AbstractScanConditionParameter.h"

namespace alinous {
class AbstractExpression;
}
using namespace alinous;

namespace codablecash {

class PlaceHolderScanCondition : public AbstractScanConditionParameter {
public:
	explicit PlaceHolderScanCondition(AbstractExpression* exp);
	virtual ~PlaceHolderScanCondition();

	virtual const UnicodeString* toStringCode() noexcept;

private:
	void resetStr() noexcept;

private:
	AbstractExpression* exp;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_PARAMS_PLACEHOLDERSCANCONDITION_H_ */
