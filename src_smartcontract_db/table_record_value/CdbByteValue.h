/*
 * CdbByteValue.h
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_VALUE_CDBBYTEVALUE_H_
#define TABLE_RECORD_VALUE_CDBBYTEVALUE_H_

#include "table_record_value/AbstractCdbValue.h"

namespace codablecash {

class CdbByteValue : public AbstractCdbValue {
public:
	CdbByteValue();
	virtual ~CdbByteValue();
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_VALUE_CDBBYTEVALUE_H_ */
