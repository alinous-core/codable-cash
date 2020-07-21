/*
 * NumericScanParam.h
 *
 *  Created on: 2020/07/21
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_PARAMS_NUMERICSCANPARAM_H_
#define SCAN_CONDITION_PARAMS_NUMERICSCANPARAM_H_

#include "scan_condition_params/AbstractScanConditionParameter.h"

namespace codablecash {

class NumericScanParam : public AbstractScanConditionParameter {
public:
	NumericScanParam();
	virtual ~NumericScanParam();
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_PARAMS_NUMERICSCANPARAM_H_ */
