/*
 * EqualityScanCondition.h
 *
 *  Created on: 2020/07/20
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_EQUALITYSCANCONDITION_H_
#define SCAN_CONDITION_EQUALITYSCANCONDITION_H_

#include "scan_condition/AbstractScanCondition.h"

using codablecash::AbstractScanCondition;

namespace alinous {

class EqualityScanCondition : public AbstractScanCondition {
public:
	EqualityScanCondition();
	virtual ~EqualityScanCondition();

private:

};

} /* namespace alinous */

#endif /* SCAN_CONDITION_EQUALITYSCANCONDITION_H_ */
