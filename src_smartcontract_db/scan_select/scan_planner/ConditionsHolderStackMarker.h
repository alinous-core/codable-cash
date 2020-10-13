/*
 * ConditionsHolderStackRelease.h
 *
 *  Created on: 2020/09/06
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_CONDITIONSHOLDERSTACKMARKER_H_
#define SCAN_PLANNER_CONDITIONSHOLDERSTACKMARKER_H_

namespace codablecash {

class ConditionsHolderStack;

class ConditionsHolderStackMarker {
public:
	explicit ConditionsHolderStackMarker(ConditionsHolderStack* stack);
	virtual ~ConditionsHolderStackMarker();

private:
	ConditionsHolderStack* stack;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_CONDITIONSHOLDERSTACKMARKER_H_ */
