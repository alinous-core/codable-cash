/*
 * FunctionCallScanCondition.h
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_EXP_FUNCTIONCALLSCANCONDITION_H_
#define SCAN_CONDITION_EXP_FUNCTIONCALLSCANCONDITION_H_

#include "scan_condition/AbstractScanCondition.h"

#include "base/ArrayList.h"

#include "scan_condition/IValueProvider.h"

namespace codablecash {

class IValueProvider;

class FunctionCallScanCondition : public AbstractScanCondition, public IValueProvider {
public:
	FunctionCallScanCondition();
	virtual ~FunctionCallScanCondition();

	virtual const UnicodeString* toStringCode() noexcept;

	void setName(UnicodeString* name) noexcept;
	void addArgument(IValueProvider* arg) noexcept;

private:
	void resetStr() noexcept;

private:
	UnicodeString* name;
	ArrayList<IValueProvider> arguments;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_EXP_FUNCTIONCALLSCANCONDITION_H_ */
