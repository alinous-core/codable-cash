/*
 * CdbOidValueList.h
 *
 *  Created on: 2020/06/01
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_VALUE_CDBOIDVALUELIST_H_
#define TABLE_RECORD_VALUE_CDBOIDVALUELIST_H_

#include "table_record_value/AbstractCdbValue.h"

#include "base/ArrayList.h"

namespace codablecash {

class CdbOid;

class CdbOidValueList : public AbstractCdbValue {
public:
	CdbOidValueList();
	virtual ~CdbOidValueList();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	void addOid(CdbOid* oid) noexcept;

	virtual AbstractCdbKey* toKey() const noexcept;
private:
	ArrayList<CdbOid> list;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_VALUE_CDBOIDVALUELIST_H_ */
