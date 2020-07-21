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
class AbstractScanConditionParameter;

class ConditionsHolder {
public:
	ConditionsHolder();
	virtual ~ConditionsHolder();

	void processExpression(AbstractScanCondition* cond);

	void push(AbstractScanCondition* cond) noexcept;
	AbstractScanCondition* top() const noexcept;
	void pop() noexcept;

	void pushParam(AbstractScanConditionParameter* param) noexcept;
	AbstractScanConditionParameter* topParam() const noexcept;
	AbstractScanConditionParameter* popParam() noexcept;

private:
	RootScanCondition* root;

	ArrayList<AbstractScanCondition> stack;
	ArrayList<AbstractScanConditionParameter> paramStack;

};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_CONDITIONSHOLDER_H_ */
