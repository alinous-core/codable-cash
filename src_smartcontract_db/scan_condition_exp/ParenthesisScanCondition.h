/*
 * ParenthesisScanCondition.h
 *
 *  Created on: 2020/07/30
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_EXP_PARENTHESISSCANCONDITION_H_
#define SCAN_CONDITION_EXP_PARENTHESISSCANCONDITION_H_

#include "scan_condition/AbstractScanCondition.h"

namespace codablecash {

class ParenthesisScanCondition : public AbstractScanCondition {
public:
	ParenthesisScanCondition();
	virtual ~ParenthesisScanCondition();

	virtual bool isContainer() const noexcept {return true;};
	virtual void addCondition(AbstractScanCondition* cond);

	virtual const UnicodeString* toStringCode() noexcept;

private:
	void resetStr() noexcept;

private:
	AbstractScanCondition* cond;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_EXP_PARENTHESISSCANCONDITION_H_ */
