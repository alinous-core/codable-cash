/*
 * RelationalScanCondition.h
 *
 *  Created on: 2020/07/29
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_EXP_RELATIONALSCANCONDITION_H_
#define SCAN_CONDITION_EXP_RELATIONALSCANCONDITION_H_

#include "scan_condition/AbstractScanCondition.h"
#include <cstdint>

namespace codablecash {

class IValueProvider;

class RelationalScanCondition : public AbstractScanCondition {
public:
	RelationalScanCondition();
	virtual ~RelationalScanCondition();

	void setLeft(IValueProvider* element);
	void setRight(IValueProvider* element);
	void setOp(uint8_t op) noexcept;

	virtual const UnicodeString* toStringCode() noexcept;

	virtual void analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner);

private:
	void resetStr() noexcept;

private:
	IValueProvider* left;
	IValueProvider* right;

	uint8_t op;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_EXP_RELATIONALSCANCONDITION_H_ */
