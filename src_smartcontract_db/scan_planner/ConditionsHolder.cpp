/*
 * ConditionsHolder.cpp
 *
 *  Created on: 2020/07/19
 *      Author: iizuka
 */

#include "scan_planner/ConditionsHolder.h"

namespace codablecash {

ConditionsHolder::ConditionsHolder() {
	this->root = nullptr;

}

ConditionsHolder::~ConditionsHolder() {
	delete this->root;
}

} /* namespace codablecash */
