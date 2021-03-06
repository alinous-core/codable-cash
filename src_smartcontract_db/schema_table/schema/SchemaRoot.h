/*
 * SchemaBinary.h
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#ifndef SCHEMA_SCHEMAROOT_H_
#define SCHEMA_SCHEMAROOT_H_
#include <cstdint>

#include "base/ArrayList.h"
#include "base/HashMap.h"

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

	void addSchema(Schema* schema) noexcept;
	Schema* getSchema(const UnicodeString* name) const noexcept;

	int binarySize() const;
	void toBinary(ByteBuffer* out) const;
	void fromBinary(ByteBuffer* in);

	uint64_t newTransactionId() noexcept;
	uint64_t newSchemaObjectId() noexcept;
	uint64_t newRecordObjectId() noexcept;

	uint64_t getSchemaObjectVersionId() const noexcept;
	void upgradeSchemaObjectVersionId() noexcept;

	const CdbTable* createTable(const CdbTable* table);

	const ArrayList<Schema>* getSchemaList() const noexcept;

	void removeTable(const UnicodeString* schema, const UnicodeString* table);

private:
	ArrayList<Schema> list;
	HashMap<UnicodeString, Schema> map;

	uint64_t maxTransactionId;
	uint64_t maxObjectId;
	uint64_t maxSchemaObjectId;

};

} /* namespace codablecash */

#endif /* SCHEMA_SCHEMAROOT_H_ */
