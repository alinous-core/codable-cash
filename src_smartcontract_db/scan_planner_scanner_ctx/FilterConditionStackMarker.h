/*
 * FilterConditionStackMarker.h
 *
 *  Created on: 2020/09/06
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_FILTERCONDITIONSTACKMARKER_H_
#define SCAN_PLANNER_SCANNER_CTX_FILTERCONDITIONSTACKMARKER_H_

namespace codablecash {

class FilterConditionStack;

class FilterConditionStackMarker {
public:
	explicit FilterConditionStackMarker(FilterConditionStack* stack);
	virtual ~FilterConditionStackMarker();

private:
	FilterConditionStack* stack;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_FILTERCONDITIONSTACKMARKER_H_ */
