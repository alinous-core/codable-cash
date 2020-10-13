/*
 * WildCardScanParam.h
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_PARAMS_WILDCARDSCANPARAM_H_
#define SCAN_CONDITION_PARAMS_WILDCARDSCANPARAM_H_

#include "scan_select/scan_condition_params/AbstractScanConditionParameter.h"

namespace codablecash {

class WildCardScanParam : public AbstractScanConditionParameter {
public:
	static const UnicodeString WILDCARD;

	WildCardScanParam();
	virtual ~WildCardScanParam();

	virtual const UnicodeString* toStringCode() noexcept;
	virtual IValueProvider* clone() const noexcept;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_PARAMS_WILDCARDSCANPARAM_H_ */
