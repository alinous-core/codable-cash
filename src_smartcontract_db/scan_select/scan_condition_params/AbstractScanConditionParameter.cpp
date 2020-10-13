/*
 * AbstractScanConditionElement.cpp
 *
 *  Created on: 2020/07/20
 *      Author: iizuka
 */

#include "scan_select/scan_condition_params/AbstractScanConditionParameter.h"

namespace codablecash {

AbstractScanConditionParameter::AbstractScanConditionParameter() {

}

AbstractScanConditionParameter::~AbstractScanConditionParameter() {

}

bool AbstractScanConditionParameter::isFilterable(VirtualMachine* vm, SelectScanPlanner* planner,
		FilterConditionDitector* detector) const noexcept {
	return true;
}


} /* namespace codablecash */
