/*
 * RelationalScanCondition.h
 *
 *  Created on: 2020/07/29
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_EXP_RELATIONALSCANCONDITION_H_
#define SCAN_CONDITION_EXP_RELATIONALSCANCONDITION_H_

#include "scan_condition/AbstractScanCondition.h"

namespace codablecash {

class IValueProvider;

class RelationalScanCondition : public AbstractScanCondition {
public:
	RelationalScanCondition();
	virtual ~RelationalScanCondition();

	void setLeft(AbstractScanConditionElement* element);
	void setRight(AbstractScanConditionElement* element);
private:
	IValueProvider* left;
	IValueProvider* right;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_EXP_RELATIONALSCANCONDITION_H_ */
