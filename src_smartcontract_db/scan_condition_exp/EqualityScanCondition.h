/*
 * EqualityScanCondition.h
 *
 *  Created on: 2020/07/20
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_EQUALITYSCANCONDITION_H_
#define SCAN_CONDITION_EQUALITYSCANCONDITION_H_

#include "scan_condition/AbstractScanCondition.h"

namespace codablecash {

class IValueProvider;

class EqualityScanCondition : public AbstractScanCondition {
public:
	EqualityScanCondition();
	virtual ~EqualityScanCondition();

	void setLeft(IValueProvider* element);
	void setRight(IValueProvider* element);

	virtual const UnicodeString* toStringCode() noexcept;

	virtual void analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner);
	virtual void collectJoinCandidate(VirtualMachine* vm, SelectScanPlanner* planner, int joinType, JoinCandidateHolder* jholder);
	virtual void detectFilterConditions(VirtualMachine* vm, SelectScanPlanner* planner, FilterConditionDitector* detector);
	virtual void detectIndexCondition(VirtualMachine* vm, SelectScanPlanner* planner, TableIndexDetector* detector);

	virtual AbstractScanCondition* cloneCondition() const noexcept;

private:
	void resetStr() noexcept;
private:
	IValueProvider* left;
	IValueProvider* right;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_EQUALITYSCANCONDITION_H_ */
