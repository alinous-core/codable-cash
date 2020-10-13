/*
 * ParenthesisScanCondition.h
 *
 *  Created on: 2020/07/30
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_EXP_PARENTHESISSCANCONDITION_H_
#define SCAN_CONDITION_EXP_PARENTHESISSCANCONDITION_H_

#include "scan_select/scan_condition/AbstractScanCondition.h"

namespace codablecash {

class ParenthesisScanCondition : public AbstractScanCondition {
public:
	ParenthesisScanCondition();
	virtual ~ParenthesisScanCondition();

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
	AbstractScanCondition* cond;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_EXP_PARENTHESISSCANCONDITION_H_ */
