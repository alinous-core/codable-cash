/*
 * CdbOidKey.h
 *
 *  Created on: 2020/09/26
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_KEY_CDBOIDKEY_H_
#define TABLE_RECORD_KEY_CDBOIDKEY_H_

#include "schema_table/record/table_record_key/AbstractCdbKey.h"

namespace codablecash {

class CdbOid;

class CdbOidKey : public AbstractCdbKey {
	friend class CdbKeyFactory;
private:
	CdbOidKey();

public:
	CdbOidKey(const CdbOidKey& inst);
	explicit CdbOidKey(const CdbOid* oid);
	virtual ~CdbOidKey();

	virtual AbstractBtreeKey* clone()  const noexcept;
	virtual int compareTo(const AbstractBtreeKey* key) const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	const CdbOid* getOid() const noexcept {
		return this->oid;
	}

private:
	CdbOid* oid;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_KEY_CDBOIDKEY_H_ */
