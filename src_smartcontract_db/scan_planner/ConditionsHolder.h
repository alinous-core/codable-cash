/*
 * ConditionsHolder.h
 *
 *  Created on: 2020/07/19
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_CONDITIONSHOLDER_H_
#define SCAN_PLANNER_CONDITIONSHOLDER_H_

namespace alinous {
class AbstractSQLExpression;
class VirtualMachine;
}
using namespace alinous;

namespace codablecash {

class RootScanCondition;
class AbstractScanCondition;
class AbstractScanConditionElement;
class SelectScanPlanner;
class ConditionsHolderStack;

class ConditionsHolder {
public:
	ConditionsHolder();
	virtual ~ConditionsHolder();

	void push(AbstractScanConditionElement* cond) noexcept;
	AbstractScanConditionElement* top() const noexcept;
	AbstractScanConditionElement* pop() noexcept;

	ConditionsHolderStack* getStack() const noexcept {
		return stack;
	}

	RootScanCondition* getRoot() const noexcept;

	void analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner);

private:
	RootScanCondition* root;

	ConditionsHolderStack* stack;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_CONDITIONSHOLDER_H_ */
