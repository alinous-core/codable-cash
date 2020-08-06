/*
 * ScanConditionCast.h
 *
 *  Created on: 2020/08/01
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_SCANCONDITIONCAST_H_
#define SCAN_CONDITION_SCANCONDITIONCAST_H_

namespace alinous {
class VirtualMachine;
class CodeElement;
}
using namespace alinous;

namespace codablecash {

class AbstractScanCondition;
class AbstractScanConditionElement;
class IValueProvider;
class ExpressionListScanCondition;

class ScanConditionCast {
public:
	static AbstractScanCondition* toAbstractScanCondition(AbstractScanConditionElement* condElement, VirtualMachine* vm, const CodeElement* element);
	static IValueProvider* toIValueProvider(AbstractScanConditionElement* condElement, VirtualMachine* vm, const CodeElement* element);
	static ExpressionListScanCondition* toExpressionList(AbstractScanConditionElement* condElement, VirtualMachine* vm, const CodeElement* element);
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_SCANCONDITIONCAST_H_ */
