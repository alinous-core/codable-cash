/*
 * ConditionsHolder.h
 *
 *  Created on: 2020/07/19
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_CONDITIONSHOLDER_H_
#define SCAN_PLANNER_CONDITIONSHOLDER_H_

#include "base/ArrayList.h"

namespace alinous {
class AbstractSQLExpression;
}
using namespace alinous;

namespace codablecash {

class RootScanCondition;
class AbstractScanCondition;
class AbstractScanConditionElement;

class ConditionsHolder {
public:
	ConditionsHolder();
	virtual ~ConditionsHolder();

	void push(AbstractScanConditionElement* cond) noexcept;
	AbstractScanConditionElement* top() const noexcept;
	AbstractScanConditionElement* pop() noexcept;

private:
	RootScanCondition* root;

	ArrayList<AbstractScanConditionElement> stack;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_CONDITIONSHOLDER_H_ */
