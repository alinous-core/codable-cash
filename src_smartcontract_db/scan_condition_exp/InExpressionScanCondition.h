/*
 * InExpressionScanCondition.h
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_EXP_INEXPRESSIONSCANCONDITION_H_
#define SCAN_CONDITION_EXP_INEXPRESSIONSCANCONDITION_H_

#include "scan_condition/AbstractScanCondition.h"

namespace codablecash {

class IValueProvider;
class ExpressionListScanCondition;

class InExpressionScanCondition : public AbstractScanCondition {
public:
	InExpressionScanCondition();
	virtual ~InExpressionScanCondition();

	virtual const UnicodeString* toStringCode() noexcept;

	void setLeft(IValueProvider* cond) noexcept;
	void setList(ExpressionListScanCondition* list) noexcept;

	virtual void analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner);

private:
	void resetStr() noexcept;

private:
	IValueProvider* left;
	ExpressionListScanCondition* list;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_EXP_INEXPRESSIONSCANCONDITION_H_ */
