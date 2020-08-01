/*
 * EqualityScanCondition.h
 *
 *  Created on: 2020/07/20
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_EQUALITYSCANCONDITION_H_
#define SCAN_CONDITION_EQUALITYSCANCONDITION_H_

#include "scan_condition/AbstractScanCondition.h"

namespace codablecash {

class IValueProvider;

class EqualityScanCondition : public AbstractScanCondition {
public:
	EqualityScanCondition();
	virtual ~EqualityScanCondition();

	void setLeft(IValueProvider* element);
	void setRight(IValueProvider* element);
private:
	IValueProvider* left;
	IValueProvider* right;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_EQUALITYSCANCONDITION_H_ */
