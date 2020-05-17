/*
 * SchemaBinary.h
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#ifndef SCHEMA_SCHEMAROOT_H_
#define SCHEMA_SCHEMAROOT_H_

#include "base/ArrayList.h"
#include <cstdint>

#include "engine/CdbBinaryObject.h"

namespace alinous {
class UnicodeString;
class ByteBuffer;
}
using namespace alinous;

namespace codablecash {

class Schema;
class CdbTable;

class SchemaRoot : public CdbBinaryObject {
public:
	SchemaRoot();
	virtual ~SchemaRoot();

	void addSchemaName(const UnicodeString* name) noexcept;

	int binarySize() const;
	void toBinary(ByteBuffer* out) const;
	void fromBinary(ByteBuffer* in);

	uint64_t newTransactionId() noexcept;
	uint64_t newSchemaObjectId() noexcept;

	void createTable(CdbTable* table);
private:
	ArrayList<Schema> list;


	uint64_t maxTransactionId;
	uint64_t maxObjectId;
	uint64_t maxSchemaObjectId;

};

} /* namespace codablecash */

#endif /* SCHEMA_SCHEMAROOT_H_ */
