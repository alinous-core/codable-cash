/*
 * ConditionFactory.h
 *
 *  Created on: 2020/07/20
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_CONDITIONFACTORY_H_
#define SCAN_PLANNER_CONDITIONFACTORY_H_

namespace codablecash {

class AbstractScanCondition;

class ConditionFactory {
public:
	static AbstractScanCondition* createScanCondition();
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_CONDITIONFACTORY_H_ */
