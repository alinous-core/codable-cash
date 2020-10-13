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

#include "schema_table/table_record_value/AbstractCdbValue.h"

namespace alinous {
class ByteBuffer;
}
using namespace alinous;

namespace codablecash {

class AbstractCdbValue;
class CdbOid;

class CdbRecord : public AbstractCdbValue {
public:
	CdbRecord(const CdbRecord& inst);
	CdbRecord();
	virtual ~CdbRecord();

	void setOid(const CdbOid* oid) noexcept;
	const CdbOid* getOid() const noexcept {
		return oid;
	}

	void initNullColumns(int num) noexcept;
	void addValue(AbstractCdbValue* value) noexcept;
	void setValue(AbstractCdbValue* value, int i) noexcept;
	void removeColumnValue(int pos) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	virtual AbstractCdbValue* copy() const noexcept;
	virtual AbstractCdbKey* toKey() const noexcept;

	static CdbRecord* createFromBinary(ByteBuffer* in);

	const ArrayList<AbstractCdbValue>* getValues() const noexcept;

	const AbstractCdbValue* get(int pos) const noexcept;

private:
	CdbOid* oid;
	ArrayList<AbstractCdbValue> list;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_CDBRECORD_H_ */
