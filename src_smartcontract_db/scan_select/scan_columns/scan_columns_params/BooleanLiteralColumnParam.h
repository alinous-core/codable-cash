/*
 * BooleanLiteralColumnParam.h
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_PARAMS_BOOLEANLITERALCOLUMNPARAM_H_
#define SCAN_COLUMNS_PARAMS_BOOLEANLITERALCOLUMNPARAM_H_

#include "scan_select/scan_columns_params/AbstractColumnParam.h"

namespace codablecash {

class BooleanLiteralColumnParam: public AbstractColumnParam {
public:
	static const UnicodeString TRUE;
	static const UnicodeString FALSE;

	explicit BooleanLiteralColumnParam(bool value);
	virtual ~BooleanLiteralColumnParam();

	virtual const UnicodeString* toStringCode() noexcept;

private:
	bool value;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_PARAMS_BOOLEANLITERALCOLUMNPARAM_H_ */
