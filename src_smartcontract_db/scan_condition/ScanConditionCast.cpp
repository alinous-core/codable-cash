/*
 * ScanConditionCast.cpp
 *
 *  Created on: 2020/08/01
 *      Author: iizuka
 */

#include "scan_condition/ScanConditionCast.h"

#include "scan_condition/AbstractScanCondition.h"
#include "scan_condition/AbstractScanConditionElement.h"

namespace codablecash {


AbstractScanCondition* ScanConditionCast::toAbstractScanCondition(AbstractScanConditionElement* element) {
	AbstractScanCondition* scanCond = dynamic_cast<AbstractScanCondition*>(element);

	if(scanCond == nullptr){

	}

	return scanCond;

}


} /* namespace codablecash */
