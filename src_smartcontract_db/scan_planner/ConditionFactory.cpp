/*
 * ConditionFactory.cpp
 *
 *  Created on: 2020/07/20
 *      Author: iizuka
 */

#include "scan_planner/ConditionFactory.h"

#include "scan_condition/AbstractScanCondition.h"

#include "engine/CdbException.h"

namespace codablecash {

AbstractScanCondition* codablecash::ConditionFactory::createScanCondition(short type) {
	AbstractScanCondition* ret = nullptr;

	switch(type){
	default:
		throw new CdbException(__FILE__, __LINE__);
	}

	return ret;
}

} /* namespace codablecash */


