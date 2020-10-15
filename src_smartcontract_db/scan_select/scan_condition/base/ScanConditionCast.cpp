/*
 * ScanConditionCast.cpp
 *
 *  Created on: 2020/08/01
 *      Author: iizuka
 */

#include "scan_select/scan_condition/base/ScanConditionCast.h"

#include "scan_select/scan_condition/base/AbstractScanCondition.h"
#include "scan_select/scan_condition/base/AbstractScanConditionElement.h"
#include "scan_select/scan_condition/base/IValueProvider.h"

#include "scan_select/scan_condition/exp/ExpressionListScanCondition.h"

#include "vm/VirtualMachine.h"

#include "instance/instance_exception/TypeCastExceptionClassDeclare.h"
#include "instance/instance_exception/ExceptionInterrupt.h"

namespace codablecash {


AbstractScanCondition* ScanConditionCast::toAbstractScanCondition(AbstractScanConditionElement* condElement, VirtualMachine* vm, const CodeElement* element) {
	AbstractScanCondition* scanCond = dynamic_cast<AbstractScanCondition*>(condElement);

	if(scanCond == nullptr){
		delete condElement;

		TypeCastExceptionClassDeclare::throwException(vm, element);
		ExceptionInterrupt::interruptPoint(vm);
	}

	return scanCond;

}

IValueProvider* ScanConditionCast::toIValueProvider(AbstractScanConditionElement* condElement, VirtualMachine* vm, const CodeElement* element) {
	IValueProvider* val = dynamic_cast<IValueProvider*>(condElement);

	if(val == nullptr){
		delete condElement;

		TypeCastExceptionClassDeclare::throwException(vm, element);
		ExceptionInterrupt::interruptPoint(vm);
	}

	return val;
}

ExpressionListScanCondition* ScanConditionCast::toExpressionList(AbstractScanConditionElement* condElement, VirtualMachine* vm, const CodeElement* element) {
	ExpressionListScanCondition* val = dynamic_cast<ExpressionListScanCondition*>(condElement);

	if(val == nullptr){
		delete condElement;

		TypeCastExceptionClassDeclare::throwException(vm, element);
		ExceptionInterrupt::interruptPoint(vm);
	}

	return val;
}


} /* namespace codablecash */
