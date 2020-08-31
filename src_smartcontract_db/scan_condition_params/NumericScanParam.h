/*
 * NumericScanParam.h
 *
 *  Created on: 2020/07/21
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_PARAMS_NUMERICSCANPARAM_H_
#define SCAN_CONDITION_PARAMS_NUMERICSCANPARAM_H_
#include <cstdlib>

#include "scan_condition_params/AbstractScanConditionParameter.h"

namespace codablecash {

class NumericScanParam : public AbstractScanConditionParameter {
public:
	NumericScanParam(const NumericScanParam& inst);
	explicit NumericScanParam(int64_t longv);
	virtual ~NumericScanParam();

	virtual const UnicodeString* toStringCode() noexcept;
	virtual AbstractScanConditionParameter* clone() const noexcept;

private:
	int64_t value;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_PARAMS_NUMERICSCANPARAM_H_ */
