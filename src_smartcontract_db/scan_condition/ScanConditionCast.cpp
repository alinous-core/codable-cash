/*
 * ScanConditionCast.cpp
 *
 *  Created on: 2020/08/01
 *      Author: iizuka
 */

#include "scan_condition/ScanConditionCast.h"

#include "scan_condition/AbstractScanCondition.h"
#include "scan_condition/AbstractScanConditionElement.h"
#include "scan_condition/IValueProvider.h"

#include "vm/VirtualMachine.h"


namespace codablecash {


AbstractScanCondition* ScanConditionCast::toAbstractScanCondition(AbstractScanConditionElement* element, VirtualMachine* vm) {
	AbstractScanCondition* scanCond = dynamic_cast<AbstractScanCondition*>(element);

	if(scanCond == nullptr){
		delete element;

	}

	return scanCond;

}

IValueProvider* codablecash::ScanConditionCast::toIValueProvider(AbstractScanConditionElement* element, VirtualMachine* vm) {
	IValueProvider* val = dynamic_cast<IValueProvider*>(element);

	if(val == nullptr){
		delete element;
	}

	return val;
}

} /* namespace codablecash */
