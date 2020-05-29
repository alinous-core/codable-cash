/*
 * CdbRecord.h
 *
 *  Created on: 2020/05/19
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_CDBRECORD_H_
#define TABLE_RECORD_CDBRECORD_H_

#include "base/ArrayList.h"

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

	void addValue(AbstractCdbValue* value) noexcept;

	int binarySize() const;
	void toBinary(ByteBuffer* out) const;
	static CdbRecord* fromBinary(ByteBuffer* in);

private:
	ArrayList<AbstractCdbValue> list;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_CDBRECORD_H_ */
