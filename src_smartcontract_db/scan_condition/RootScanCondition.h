/*
 * RootScanCondition.h
 *
 *  Created on: 2020/06/14
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_ROOTSCANCONDITION_H_
#define SCAN_CONDITION_ROOTSCANCONDITION_H_

#include "scan_condition/AbstractScanCondition.h"

namespace codablecash {

class RootScanCondition : public AbstractScanCondition {
public:
	RootScanCondition();
	virtual ~RootScanCondition();
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_ROOTSCANCONDITION_H_ */
