/*
 * ExpressionListScanCondition.h
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_EXP_EXPRESSIONLISTSCANCONDITION_H_
#define SCAN_CONDITION_EXP_EXPRESSIONLISTSCANCONDITION_H_

#include "scan_condition/AbstractScanCondition.h"

namespace codablecash {

class ExpressionListScanCondition : public AbstractScanCondition {
public:
	ExpressionListScanCondition();
	virtual ~ExpressionListScanCondition();

	virtual const UnicodeString* toStringCode() noexcept;

private:
	void resetStr() noexcept;

private:

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_EXP_EXPRESSIONLISTSCANCONDITION_H_ */
