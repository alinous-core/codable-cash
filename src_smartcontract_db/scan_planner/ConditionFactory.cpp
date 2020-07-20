/*
 * ConditionFactory.cpp
 *
 *  Created on: 2020/07/20
 *      Author: iizuka
 */

#include "scan_planner/ConditionFactory.h"

#include "scan_condition/AbstractScanCondition.h"
#include "scan_condition/EqualityScanCondition.h"

#include "engine/CdbException.h"

#include "sc/CodeElement.h"


namespace codablecash {

AbstractScanCondition* ConditionFactory::createScanCondition(short type) {
	AbstractScanCondition* ret = nullptr;

	switch(type){
	case CodeElement::SQL_EXP_EQUALITY:
		ret = new EqualityScanCondition();
		break;
	default:
		throw new CdbException(__FILE__, __LINE__);
	}

	return ret;
}

} /* namespace codablecash */


