/*
 * SelectScanPlanner.h
 *
 *  Created on: 2020/07/19
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SELECTSCANPLANNER_H_
#define SCAN_PLANNER_SELECTSCANPLANNER_H_

namespace alinous {
class AbstractSQLExpression;
}
using namespace alinous;

namespace codablecash {

class ConditionsHolder;
class AbstractScanCondition;
class AbstractScanConditionElement;

class SelectScanPlanner {
public:
	SelectScanPlanner();
	virtual ~SelectScanPlanner();

	void processExpression(AbstractScanCondition* sqlExpression);

	void pushParam(AbstractScanConditionElement* param) noexcept;
	AbstractScanConditionElement* popParam() noexcept;

	ConditionsHolder* getConditions() const noexcept {
		return this->conditions;
	}

private:
	ConditionsHolder* conditions;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SELECTSCANPLANNER_H_ */
