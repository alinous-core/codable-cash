/*
 * CdbStringValue.h
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_VALUE_CDBSTRINGVALUE_H_
#define TABLE_RECORD_VALUE_CDBSTRINGVALUE_H_

#include "table_record_value/AbstractCdbValue.h"

namespace codablecash {

class CdbStringValue : public AbstractCdbValue {
public:
	CdbStringValue();
	virtual ~CdbStringValue();
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_VALUE_CDBSTRINGVALUE_H_ */
