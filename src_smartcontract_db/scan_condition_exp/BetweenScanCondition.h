/*
 * BetweenScanCondition.h
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_EXP_BETWEENSCANCONDITION_H_
#define SCAN_CONDITION_EXP_BETWEENSCANCONDITION_H_

#include "scan_condition/AbstractScanCondition.h"

namespace codablecash {

class IValueProvider;

class BetweenScanCondition : public AbstractScanCondition {
public:
	BetweenScanCondition();
	virtual ~BetweenScanCondition();

	void setLeft(IValueProvider* left) noexcept;
	void setStart(IValueProvider* start) noexcept;
	void setEnd(IValueProvider* end) noexcept;
private:
	IValueProvider* left;
	IValueProvider* start;
	IValueProvider* end;


};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_EXP_BETWEENSCANCONDITION_H_ */
