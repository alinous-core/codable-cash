/*
 * NotScanCondition.h
 *
 *  Created on: 2020/07/29
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_LOGICAL_NOTSCANCONDITION_H_
#define SCAN_CONDITION_LOGICAL_NOTSCANCONDITION_H_

#include "scan_select/scan_condition/base/AbstractScanCondition.h"

namespace codablecash {

class NotScanCondition : public AbstractScanCondition {
public:
	NotScanCondition();
	virtual ~NotScanCondition();

	virtual bool isContainer() const noexcept;
	virtual void addCondition(AbstractScanCondition* cond);

	virtual const UnicodeString* toStringCode() noexcept;
	virtual AbstractScanCondition* cloneCondition() const noexcept;

	virtual void detectFilterConditions(VirtualMachine* vm, SelectScanPlanner* planner, FilterConditionDitector* detector);
	virtual void detectIndexCondition(VirtualMachine* vm, SelectScanPlanner* planner, TableIndexDetector* detector);

private:
	void resetStr() noexcept;

private:
	AbstractScanCondition* cond;
	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_LOGICAL_NOTSCANCONDITION_H_ */
