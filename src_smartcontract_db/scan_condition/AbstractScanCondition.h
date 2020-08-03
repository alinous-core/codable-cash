/*
 * AbstractScanCondition.h
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_ABSTRACTSCANCONDITION_H_
#define SCAN_CONDITION_ABSTRACTSCANCONDITION_H_

#include "scan_condition/AbstractScanConditionElement.h"

namespace codablecash {

class AbstractScanCondition : public AbstractScanConditionElement {
public:
	explicit AbstractScanCondition(short type);
	virtual ~AbstractScanCondition();

	virtual bool isContainer() const noexcept;
private:
	short type;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_ABSTRACTSCANCONDITION_H_ */
