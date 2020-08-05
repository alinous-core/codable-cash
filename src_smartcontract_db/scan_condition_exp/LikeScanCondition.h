/*
 * LikeScanCondition.h
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_EXP_LIKESCANCONDITION_H_
#define SCAN_CONDITION_EXP_LIKESCANCONDITION_H_

#include "scan_condition/AbstractScanCondition.h"

namespace codablecash {

class LikeScanCondition : public AbstractScanCondition {
public:
	LikeScanCondition();
	virtual ~LikeScanCondition();
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_EXP_LIKESCANCONDITION_H_ */
