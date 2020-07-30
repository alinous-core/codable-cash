/*
 * AndScanCondition.h
 *
 *  Created on: 2020/07/30
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_LOGICAL_ANDSCANCONDITION_H_
#define SCAN_CONDITION_LOGICAL_ANDSCANCONDITION_H_

#include "scan_condition/AbstractScanCondition.h"

namespace codablecash {

class AndScanCondition : public AbstractScanCondition {
public:
	AndScanCondition();
	virtual ~AndScanCondition();
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_LOGICAL_ANDSCANCONDITION_H_ */
