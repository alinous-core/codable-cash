/*
 * ConditionsHolderStackRelease.cpp
 *
 *  Created on: 2020/09/06
 *      Author: iizuka
 */

#include "scan_select/scan_planner/ConditionsHolderStackMarker.h"

#include "scan_select/scan_planner/ConditionsHolderStack.h"

namespace codablecash {

ConditionsHolderStackMarker::ConditionsHolderStackMarker(ConditionsHolderStack* stack) {
	this->stack = stack;
	stack->mark();
}

ConditionsHolderStackMarker::~ConditionsHolderStackMarker() {
	this->stack->unmark();
}

} /* namespace codablecash */
