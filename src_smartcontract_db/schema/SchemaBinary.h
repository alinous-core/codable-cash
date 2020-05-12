/*
 * SchemaBinary.h
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#ifndef SCHEMA_SCHEMABINARY_H_
#define SCHEMA_SCHEMABINARY_H_

#include "base/ArrayList.h"
#include <cstdint>

namespace alinous {
class UnicodeString;
class ByteBuffer;
}
using namespace alinous;

namespace codablecash {

class SchemaBinary {
public:
	SchemaBinary();
	virtual ~SchemaBinary();

	void addSchemaName(const UnicodeString* name) noexcept;

	int binarySize() const noexcept;
	void toBinary(ByteBuffer* out) const;
	void fromBinary(ByteBuffer* in);

	uint64_t newTransactionId() noexcept;
private:
	int stringSize(UnicodeString* str) const noexcept;
	void putString(ByteBuffer* out, UnicodeString* str) const noexcept;
	UnicodeString* getString(ByteBuffer* in) const noexcept;
private:
	ArrayList<UnicodeString> list;
	uint64_t maxTransactionId;
	uint64_t maxObjectId;
};

} /* namespace codablecash */

#endif /* SCHEMA_SCHEMABINARY_H_ */
