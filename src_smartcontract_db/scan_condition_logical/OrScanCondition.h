/*
 * OrScanCondition.h
 *
 *  Created on: 2020/07/30
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_LOGICAL_ORSCANCONDITION_H_
#define SCAN_CONDITION_LOGICAL_ORSCANCONDITION_H_

#include "scan_condition/AbstractScanCondition.h"
#include "base/ArrayList.h"

using namespace alinous;

namespace codablecash {

class OrScanCondition : public AbstractScanCondition {
public:
	OrScanCondition();
	virtual ~OrScanCondition();

	virtual bool isContainer() const noexcept {return true;};
	virtual void addCondition(AbstractScanCondition* cond);

private:
	ArrayList<AbstractScanCondition> list;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_LOGICAL_ORSCANCONDITION_H_ */
