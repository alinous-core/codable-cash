/*
 * ConditionStackPopper.h
 *
 *  Created on: 2020/07/21
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_CONDITIONSTACKPOPPER_H_
#define SCAN_PLANNER_CONDITIONSTACKPOPPER_H_

namespace codablecash {

class SelectScanPlanner;
class ConditionsHolder;

class ConditionStackPopper {
public:
	ConditionStackPopper(SelectScanPlanner* planner);
	virtual ~ConditionStackPopper();

private:
	ConditionsHolder* conditions;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_CONDITIONSTACKPOPPER_H_ */
