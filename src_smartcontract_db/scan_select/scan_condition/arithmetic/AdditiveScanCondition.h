/*
 * AdditiveScanCondition.h
 *
 *  Created on: 2020/07/31
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_ARITHMETIC_ADDITIVESCANCONDITION_H_
#define SCAN_CONDITION_ARITHMETIC_ADDITIVESCANCONDITION_H_

#include <cstdint>
#include "base/ArrayList.h"
#include "base/RawArrayPrimitive.h"

#include "scan_select/scan_condition/base/AbstractScanCondition.h"
#include "scan_select/scan_condition/base/IValueProvider.h"

using namespace alinous;

namespace codablecash {

class AdditiveScanCondition : public AbstractScanCondition, public IValueProvider{
public:
	AdditiveScanCondition();
	virtual ~AdditiveScanCondition();

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

#endif /* SCAN_CONDITION_ARITHMETIC_ADDITIVESCANCONDITION_H_ */
