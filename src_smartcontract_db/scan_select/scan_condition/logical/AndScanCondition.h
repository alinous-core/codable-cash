/*
 * AndScanCondition.h
 *
 *  Created on: 2020/07/30
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_LOGICAL_ANDSCANCONDITION_H_
#define SCAN_CONDITION_LOGICAL_ANDSCANCONDITION_H_

#include "scan_select/scan_condition/base/AbstractScanCondition.h"
#include "base/ArrayList.h"

using namespace alinous;

namespace codablecash {

class AndScanCondition : public AbstractScanCondition {
public:
	AndScanCondition();
	virtual ~AndScanCondition();

	virtual bool isContainer() const noexcept {return true;};
	virtual void addCondition(AbstractScanCondition* cond);

	virtual const UnicodeString* toStringCode() noexcept;

	virtual void analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner);
	virtual void collectJoinCandidate(VirtualMachine* vm, SelectScanPlanner* planner, int joinType, JoinCandidateHolder* jholder);
	virtual void detectFilterConditions(VirtualMachine* vm, SelectScanPlanner* planner, FilterConditionDitector* detector);
	virtual void detectIndexCondition(VirtualMachine* vm, SelectScanPlanner* planner, TableIndexDetector* detector);

	virtual AbstractScanCondition* cloneCondition() const noexcept;

private:
	void resetStr() noexcept;

private:
	ArrayList<AbstractScanCondition> list;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_LOGICAL_ANDSCANCONDITION_H_ */
