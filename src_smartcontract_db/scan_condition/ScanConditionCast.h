/*
 * ScanConditionCast.h
 *
 *  Created on: 2020/08/01
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_SCANCONDITIONCAST_H_
#define SCAN_CONDITION_SCANCONDITIONCAST_H_

namespace codablecash {

class AbstractScanCondition;
class AbstractScanConditionElement;

class ScanConditionCast {
	static AbstractScanCondition* toAbstractScanCondition(AbstractScanConditionElement* element);
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_SCANCONDITIONCAST_H_ */
