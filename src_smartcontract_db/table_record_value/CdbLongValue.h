/*
 * CdbLongValue.h
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_VALUE_CDBLONGVALUE_H_
#define TABLE_RECORD_VALUE_CDBLONGVALUE_H_

#include "table_record_value/AbstractCdbValue.h"

namespace codablecash {

class CdbLongValue : public AbstractCdbValue {
public:
	CdbLongValue();
	virtual ~CdbLongValue();
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_VALUE_CDBLONGVALUE_H_ */
