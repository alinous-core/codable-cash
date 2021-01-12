/*
 * MultipleValueProvidorScanParam.h
 *
 *  Created on: 2021/01/12
 *      Author: iizuka
 */

#ifndef SCAN_SELECT_SCAN_CONDITION_PARAMS_MULTIPLEVALUEPROVIDORSCANPARAM_H_
#define SCAN_SELECT_SCAN_CONDITION_PARAMS_MULTIPLEVALUEPROVIDORSCANPARAM_H_

#include "scan_select/scan_condition/params/AbstractScanConditionParameter.h"

#include "base/ArrayList.h"

namespace codablecash {

class IValueProvider;

class MultipleValueProvidorScanParam : public AbstractScanConditionParameter {
public:
	MultipleValueProvidorScanParam(const MultipleValueProvidorScanParam& inst);
	MultipleValueProvidorScanParam();
	virtual ~MultipleValueProvidorScanParam();

	virtual void analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner);

	virtual const UnicodeString* toStringCode() noexcept;
	virtual IValueProvider* clone() const noexcept;

private:
	ArrayList<IValueProvider> list;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_SELECT_SCAN_CONDITION_PARAMS_MULTIPLEVALUEPROVIDORSCANPARAM_H_ */
