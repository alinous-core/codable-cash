/*
 * Schema.h
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#ifndef SCHEMA_SCHEMA_H_
#define SCHEMA_SCHEMA_H_

#include "engine/CdbBinaryObject.h"
#include <cstdint>

namespace alinous {
class ByteBuffer;
}
using namespace alinous;

namespace codablecash {

class CdbOid;

class Schema : public CdbBinaryObject {
public:
	static const constexpr uint8_t CDB_OBJ_TYPE{4};
	Schema(uint64_t oid);
	virtual ~Schema();

	void setOid(uint64_t oid) noexcept;
	void setName(UnicodeString* name) noexcept;

	int binarySize() const;
	void toBinary(ByteBuffer* out) const;
	void fromBinary(ByteBuffer* in);

private:
	CdbOid* oid;

	UnicodeString* name;
};

} /* namespace codablecash */

#endif /* SCHEMA_SCHEMA_H_ */
