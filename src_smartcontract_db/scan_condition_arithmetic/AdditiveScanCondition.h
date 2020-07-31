/*
 * AdditiveScanCondition.h
 *
 *  Created on: 2020/07/31
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_ARITHMETIC_ADDITIVESCANCONDITION_H_
#define SCAN_CONDITION_ARITHMETIC_ADDITIVESCANCONDITION_H_

#include "base/ArrayList.h"

#include "scan_condition/AbstractScanCondition.h"
#include "scan_condition/IValueProvider.h"

using namespace alinous;

namespace codablecash {

class AdditiveScanCondition : public AbstractScanCondition, public IValueProvider{
public:
	AdditiveScanCondition();
	virtual ~AdditiveScanCondition();

private:
	ArrayList<IValueProvider> list;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_ARITHMETIC_ADDITIVESCANCONDITION_H_ */
