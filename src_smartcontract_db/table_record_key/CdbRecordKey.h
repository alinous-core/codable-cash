/*
 * CdbRecordKey.h
 *
 *  Created on: 2020/05/30
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_KEY_CDBRECORDKEY_H_
#define TABLE_RECORD_KEY_CDBRECORDKEY_H_

#include "table_record_key/AbstractCdbKey.h"

#include "base/ArrayList.h"

namespace codablecash {

class CdbRecordKey : public AbstractCdbKey {
public:
	CdbRecordKey(const CdbRecordKey& inst);
	CdbRecordKey();
	virtual ~CdbRecordKey();

	virtual AbstractBtreeKey* clone()  const noexcept;
	virtual int compareTo(const AbstractBtreeKey* key) const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	void addKey(AbstractBtreeKey* key) noexcept;
private:
	ArrayList<AbstractBtreeKey> list;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_KEY_CDBRECORDKEY_H_ */
