/*
 * StringLiteralColumnParam.h
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_PARAMS_STRINGLITERALCOLUMNPARAM_H_
#define SCAN_COLUMNS_PARAMS_STRINGLITERALCOLUMNPARAM_H_

#include "scan_select/scan_columns/scan_columns_params/AbstractColumnParam.h"

namespace alinous {
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class StringLiteralColumnParam : public AbstractColumnParam {
public:
	explicit StringLiteralColumnParam(const UnicodeString* str);
	virtual ~StringLiteralColumnParam();

	virtual const UnicodeString* toStringCode() noexcept;

private:
	UnicodeString* value;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_PARAMS_STRINGLITERALCOLUMNPARAM_H_ */
