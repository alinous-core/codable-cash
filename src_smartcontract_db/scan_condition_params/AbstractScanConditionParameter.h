/*
 * AbstractScanConditionElement.h
 *
 *  Created on: 2020/07/20
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_PARAMS_ABSTRACTSCANCONDITIONPARAMETER_H_
#define SCAN_CONDITION_PARAMS_ABSTRACTSCANCONDITIONPARAMETER_H_

#include "scan_condition/AbstractScanConditionElement.h"

#include "scan_condition/IValueProvider.h"

namespace codablecash {

class AbstractScanConditionParameter : public AbstractScanConditionElement, public IValueProvider {
public:
	AbstractScanConditionParameter();
	virtual ~AbstractScanConditionParameter();
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_PARAMS_ABSTRACTSCANCONDITIONPARAMETER_H_ */
