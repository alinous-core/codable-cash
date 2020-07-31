/*
 * BooleanScanParam.h
 *
 *  Created on: 2020/07/27
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_PARAMS_BOOLEANSCANPARAM_H_
#define SCAN_CONDITION_PARAMS_BOOLEANSCANPARAM_H_

#include "scan_condition_params/AbstractScanConditionParameter.h"

namespace codablecash {

class BooleanScanParam : public AbstractScanConditionParameter, public IValueProvider {
public:
	explicit BooleanScanParam(bool value);
	virtual ~BooleanScanParam();

private:
	bool value;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_PARAMS_BOOLEANSCANPARAM_H_ */
