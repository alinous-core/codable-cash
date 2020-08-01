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
}
using namespace alinous;

namespace codablecash {

class AbstractScanCondition;
class AbstractScanConditionElement;
class IValueProvider;

class ScanConditionCast {
public:
	static AbstractScanCondition* toAbstractScanCondition(AbstractScanConditionElement* element, VirtualMachine* vm);
	static IValueProvider* toIValueProvider(AbstractScanConditionElement* element, VirtualMachine* vm);
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_SCANCONDITIONCAST_H_ */
