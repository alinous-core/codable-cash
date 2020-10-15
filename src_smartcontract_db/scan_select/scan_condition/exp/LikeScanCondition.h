/*
 * LikeScanCondition.h
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_EXP_LIKESCANCONDITION_H_
#define SCAN_CONDITION_EXP_LIKESCANCONDITION_H_

#include "scan_select/scan_condition/base/AbstractScanCondition.h"

namespace codablecash {

class IValueProvider;

class LikeScanCondition : public AbstractScanCondition {
public:
	LikeScanCondition();
	virtual ~LikeScanCondition();

	void setLeft(IValueProvider* left) noexcept;
	void setRight(IValueProvider* right) noexcept;
	void setEscape(IValueProvider* escape) noexcept;

	virtual const UnicodeString* toStringCode() noexcept;

	virtual void analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner);
	virtual void detectFilterConditions(VirtualMachine* vm, SelectScanPlanner* planner, FilterConditionDitector* detector);
	virtual void detectIndexCondition(VirtualMachine* vm, SelectScanPlanner* planner, TableIndexDetector* detector);


	virtual AbstractScanCondition* cloneCondition() const noexcept;

private:
	void resetStr() noexcept;

private:
	IValueProvider* left;
	IValueProvider* right;
	IValueProvider* escape;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_EXP_LIKESCANCONDITION_H_ */
