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

class ConditionsHolder {
public:
	ConditionsHolder();
	virtual ~ConditionsHolder();

	void processExpression(AbstractScanCondition* cond);

	void push(AbstractScanCondition* cond) noexcept;
	AbstractScanCondition* top() const noexcept;
	void pop() noexcept;
private:
	RootScanCondition* root;

	ArrayList<AbstractScanCondition> stack;

};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_CONDITIONSHOLDER_H_ */
