/*
 * OrScanCondition.h
 *
 *  Created on: 2020/07/30
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_LOGICAL_ORSCANCONDITION_H_
#define SCAN_CONDITION_LOGICAL_ORSCANCONDITION_H_

#include "scan_condition/AbstractScanCondition.h"

namespace codablecash {

class OrScanCondition : public AbstractScanCondition {
public:
	OrScanCondition();
	virtual ~OrScanCondition();
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_LOGICAL_ORSCANCONDITION_H_ */
