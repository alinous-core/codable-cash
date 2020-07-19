/*
 * SelectScanPlanner.cpp
 *
 *  Created on: 2020/07/19
 *      Author: iizuka
 */

#include "scan_planner/SelectScanPlanner.h"

#include "scan_planner/ConditionsHolder.h"


namespace codablecash {

SelectScanPlanner::SelectScanPlanner() {
	this->conditions = new ConditionsHolder();

}

SelectScanPlanner::~SelectScanPlanner() {
	delete this->conditions;
}

} /* namespace codablecash */
