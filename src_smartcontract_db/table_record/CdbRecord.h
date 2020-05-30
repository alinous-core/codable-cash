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

namespace alinous {
class ByteBuffer;
}
using namespace alinous;

namespace codablecash {

class AbstractCdbValue;

class CdbRecord {
public:
	CdbRecord();
	virtual ~CdbRecord();

	void setOid(uint64_t oid) noexcept;

	void addValue(AbstractCdbValue* value) noexcept;

	int binarySize() const;
	void toBinary(ByteBuffer* out) const;
	static CdbRecord* fromBinary(ByteBuffer* in);

	const ArrayList<AbstractCdbValue>* getValues() const noexcept;

private:
	uint64_t oid;
	ArrayList<AbstractCdbValue> list;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_CDBRECORD_H_ */
