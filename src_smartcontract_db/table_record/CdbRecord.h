/*
 * CdbRecord.h
 *
 *  Created on: 2020/05/19
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_CDBRECORD_H_
#define TABLE_RECORD_CDBRECORD_H_

#include "base/ArrayList.h"
#include <cstdint>

#include "table_record_value/AbstractCdbValue.h"

namespace alinous {
class ByteBuffer;
}
using namespace alinous;

namespace codablecash {

class AbstractCdbValue;

class CdbRecord : public AbstractCdbValue {
public:
	CdbRecord(const CdbRecord& inst);
	CdbRecord();
	virtual ~CdbRecord();

	void setOid(uint64_t oid) noexcept;
	uint64_t getOid() const noexcept {
		return oid;
	}

	void initNullColumns(int num) noexcept;
	void addValue(AbstractCdbValue* value) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	virtual AbstractCdbValue* copy() const noexcept;
	virtual AbstractCdbKey* toKey() const noexcept;

	static CdbRecord* createFromBinary(ByteBuffer* in);

	const ArrayList<AbstractCdbValue>* getValues() const noexcept;

	const AbstractCdbValue* get(int pos) const noexcept;

private:
	uint64_t oid;
	ArrayList<AbstractCdbValue> list;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_CDBRECORD_H_ */
