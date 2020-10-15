/*
 * TableIndexDetectorStackMarker.cpp
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index/TableIndexDetectorStackMarker.h"
#include "scan_select/scan_planner/scanner/index/TableIndexDetectorStack.h"

namespace codablecash {

TableIndexDetectorStackMarker::TableIndexDetectorStackMarker(TableIndexDetectorStack* stack) {
	this->stack = stack;
	stack->mark();
}

TableIndexDetectorStackMarker::~TableIndexDetectorStackMarker() {
	this->stack->unmark();
}

} /* namespace codablecash */
