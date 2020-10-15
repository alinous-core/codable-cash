/*
 * InExpressionScanCondition.h
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_EXP_INEXPRESSIONSCANCONDITION_H_
#define SCAN_CONDITION_EXP_INEXPRESSIONSCANCONDITION_H_

#include "scan_select/scan_condition/base/AbstractScanCondition.h"

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
	virtual void detectFilterConditions(VirtualMachine* vm, SelectScanPlanner* planner, FilterConditionDitector* detector);
	virtual void detectIndexCondition(VirtualMachine* vm, SelectScanPlanner* planner, TableIndexDetector* detector);

	virtual AbstractScanCondition* cloneCondition() const noexcept;

private:
	void resetStr() noexcept;

private:
	IValueProvider* left;
	ExpressionListScanCondition* list;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_EXP_INEXPRESSIONSCANCONDITION_H_ */
