/*
 * InExpressionScanCondition.h
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_EXP_INEXPRESSIONSCANCONDITION_H_
#define SCAN_CONDITION_EXP_INEXPRESSIONSCANCONDITION_H_

#include "scan_condition/AbstractScanCondition.h"

namespace codablecash {

class InExpressionScanCondition : public AbstractScanCondition {
public:
	InExpressionScanCondition();
	virtual ~InExpressionScanCondition();
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_EXP_INEXPRESSIONSCANCONDITION_H_ */
