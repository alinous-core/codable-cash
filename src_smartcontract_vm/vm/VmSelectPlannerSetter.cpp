/*
 * VmSelectPlannerSetter.cpp
 *
 *  Created on: 2020/07/19
 *      Author: iizuka
 */

#include "vm/VmSelectPlannerSetter.h"
#include "vm/VirtualMachine.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"

namespace alinous {

VmSelectPlannerSetter::VmSelectPlannerSetter(VirtualMachine* vm, SelectScanPlanner* planner) {
	this->vm = vm;
	this->vm->setSelectPlanner(planner);
}

VmSelectPlannerSetter::~VmSelectPlannerSetter() {
	this->vm->popSelectPlanner();
}

} /* namespace alinous */
