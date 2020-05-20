/*
 * CdbShortValue.h
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_VALUE_CDBSHORTVALUE_H_
#define TABLE_RECORD_VALUE_CDBSHORTVALUE_H_

#include "table_record_value/AbstractCdbValue.h"

namespace codablecash {

class CdbShortValue : public AbstractCdbValue {
public:
	CdbShortValue();
	virtual ~CdbShortValue();
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_VALUE_CDBSHORTVALUE_H_ */
