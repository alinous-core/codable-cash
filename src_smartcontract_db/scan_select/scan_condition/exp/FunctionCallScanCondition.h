/*
 * FunctionCallScanCondition.h
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_EXP_FUNCTIONCALLSCANCONDITION_H_
#define SCAN_CONDITION_EXP_FUNCTIONCALLSCANCONDITION_H_

#include "scan_select/scan_condition/base/AbstractScanCondition.h"

#include "base/ArrayList.h"

#include "scan_select/scan_condition/base/IValueProvider.h"

namespace codablecash {

class IValueProvider;

class FunctionCallScanCondition : public AbstractScanCondition, public IValueProvider {
public:
	FunctionCallScanCondition(const FunctionCallScanCondition& inst);
	FunctionCallScanCondition();
	virtual ~FunctionCallScanCondition();

	virtual const UnicodeString* toStringCode() noexcept;

	void setName(UnicodeString* name) noexcept;
	void addArgument(IValueProvider* arg) noexcept;

	virtual void analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner);
	virtual bool isFilterable(VirtualMachine* vm, SelectScanPlanner* planner, FilterConditionDitector* detector) const noexcept;
	virtual void detectFilterConditions(VirtualMachine* vm, SelectScanPlanner* planner, FilterConditionDitector* detector);
	virtual void detectIndexCondition(VirtualMachine* vm, SelectScanPlanner* planner, TableIndexDetector* detector);


	virtual IValueProvider* clone() const noexcept;
	virtual AbstractScanCondition* cloneCondition() const noexcept;

private:
	void resetStr() noexcept;

private:
	UnicodeString* name;
	ArrayList<IValueProvider> arguments;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_EXP_FUNCTIONCALLSCANCONDITION_H_ */
