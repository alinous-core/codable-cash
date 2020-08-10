/*
 * LikeScanCondition.h
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_EXP_LIKESCANCONDITION_H_
#define SCAN_CONDITION_EXP_LIKESCANCONDITION_H_

#include "scan_condition/AbstractScanCondition.h"

namespace codablecash {

class IValueProvider;

class LikeScanCondition : public AbstractScanCondition {
public:
	LikeScanCondition();
	virtual ~LikeScanCondition();

	void setLeft(IValueProvider* left) noexcept;
	void setRight(IValueProvider* right) noexcept;
	void setEscape(IValueProvider* escape) noexcept;

	virtual const UnicodeString* toStringCode() noexcept;

private:
	void resetStr() noexcept;

private:
	IValueProvider* left;
	IValueProvider* right;
	IValueProvider* escape;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_EXP_LIKESCANCONDITION_H_ */
