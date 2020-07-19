/*
 * SelectScanPlanner.h
 *
 *  Created on: 2020/07/19
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SELECTSCANPLANNER_H_
#define SCAN_PLANNER_SELECTSCANPLANNER_H_

namespace codablecash {

class ConditionsHolder;

class SelectScanPlanner {
public:
	SelectScanPlanner();
	virtual ~SelectScanPlanner();

private:
	ConditionsHolder* conditions;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SELECTSCANPLANNER_H_ */
