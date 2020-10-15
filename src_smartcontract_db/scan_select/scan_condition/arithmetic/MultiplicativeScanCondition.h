/*
 * MultiplicativeScanCondition.h
 *
 *  Created on: 2020/08/04
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_ARITHMETIC_MULTIPLICATIVESCANCONDITION_H_
#define SCAN_CONDITION_ARITHMETIC_MULTIPLICATIVESCANCONDITION_H_

#include <cstdint>

#include "scan_select/scan_condition/base/AbstractScanCondition.h"
#include "scan_select/scan_condition/base/IValueProvider.h"

#include "base/ArrayList.h"
#include "base/RawArrayPrimitive.h"


namespace codablecash {

class MultiplicativeScanCondition : public AbstractScanCondition, public IValueProvider {
public:
	MultiplicativeScanCondition();
	virtual ~MultiplicativeScanCondition();

	virtual const UnicodeString* toStringCode() noexcept;

	void addOperand(IValueProvider* vp) noexcept;
	void addOperator(uint8_t op) noexcept;

	virtual void analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner);
	virtual bool isFilterable(VirtualMachine* vm, SelectScanPlanner* planner, FilterConditionDitector* detector) const noexcept;
	virtual void detectFilterConditions(VirtualMachine* vm, SelectScanPlanner* planner, FilterConditionDitector* detector);
	virtual void detectIndexCondition(VirtualMachine* vm, SelectScanPlanner* planner, TableIndexDetector* detector);

	virtual IValueProvider* clone() const noexcept;
	virtual AbstractScanCondition* cloneCondition() const noexcept;

private:
	void resetStr() noexcept;

private:
	ArrayList<IValueProvider> list;
	RawArrayPrimitive<uint8_t> operations;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_ARITHMETIC_MULTIPLICATIVESCANCONDITION_H_ */
