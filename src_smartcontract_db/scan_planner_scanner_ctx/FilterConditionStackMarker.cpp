/*
 * FilterConditionStackMarker.cpp
 *
 *  Created on: 2020/09/06
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx/FilterConditionStackMarker.h"

#include "scan_planner_scanner_ctx/FilterConditionStack.h"

namespace codablecash {

FilterConditionStackMarker::FilterConditionStackMarker(FilterConditionStack* stack) {
	this->stack = stack;
	stack->mark();
}

FilterConditionStackMarker::~FilterConditionStackMarker() {
	this->stack->unmark();
}

} /* namespace codablecash */
