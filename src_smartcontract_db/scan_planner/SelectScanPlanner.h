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
class TablesHolder;

class SelectScanPlanner {
public:
	SelectScanPlanner();
	virtual ~SelectScanPlanner();

	void push(AbstractScanConditionElement* cond) noexcept;
	AbstractScanConditionElement* top() const noexcept;
	AbstractScanConditionElement* pop() noexcept;

	ConditionsHolder* getConditions() const noexcept {
		return this->conditions;
	}

	TablesHolder* getTablesHolder() const noexcept {
		return tablesHolder;
	}

private:
	ConditionsHolder* conditions;

	TablesHolder* tablesHolder;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SELECTSCANPLANNER_H_ */
