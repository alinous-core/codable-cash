/*
 * FilterConditionDitector.h
 *
 *  Created on: 2020/09/02
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_FILTERCONDITIONDITECTOR_H_
#define SCAN_PLANNER_SCANNER_CTX_FILTERCONDITIONDITECTOR_H_

#include "base/ArrayList.h"

namespace alinous {
class VirtualMachine;
}
using namespace alinous;

namespace codablecash {

class SelectScanPlanner;
class AbstractScanTableTarget;
class AbstractScanCondition;
class FilterConditionStack;

class FilterConditionDitector {
public:
	FilterConditionDitector(VirtualMachine* vm, SelectScanPlanner* planner);
	virtual ~FilterConditionDitector();

	void detect(AbstractScanTableTarget* target);
	bool hasTarget(const AbstractScanTableTarget* target) const noexcept;

	bool isEmpty() const noexcept;
	void push(AbstractScanCondition* cond) noexcept;
	AbstractScanCondition* pop() noexcept;
	FilterConditionStack* getStack() const noexcept {
		return stack;
	}

	AbstractScanCondition* getCondition() const noexcept {
		return this->cond;
	}
private:
	FilterConditionStack* stack;

	VirtualMachine* vm;
	SelectScanPlanner* planner;
	ArrayList<AbstractScanTableTarget> list;

	AbstractScanCondition* cond;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_FILTERCONDITIONDITECTOR_H_ */
