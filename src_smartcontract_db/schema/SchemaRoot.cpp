/*
 * SchemaBinary.cpp
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#include "schema/SchemaRoot.h"
#include "schema/Schema.h"

#include "base/UnicodeString.h"

#include "base_io/ByteBuffer.h"

#include "table/TableObjectFactory.h"

namespace codablecash {

SchemaRoot::SchemaRoot() {
	this->maxTransactionId = 0;
	this->maxObjectId = 0;
	this->maxSchemaObjectId = 0;
}

SchemaRoot::~SchemaRoot() {
	this->list.deleteElements();
}

void SchemaRoot::addSchemaName(const UnicodeString* name) noexcept {
	this->maxSchemaObjectId++;

	Schema* schema = new Schema(this->maxSchemaObjectId);
	schema->setName(new UnicodeString(name));

	this->list.addElement(schema);
}

int SchemaRoot::binarySize() const {
	int total = 0;

	total += sizeof(uint64_t) * 3;

	total += sizeof(uint32_t);
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		Schema* schema = this->list.get(i);

		total += schema->binarySize();
	}

	return total;
}

void SchemaRoot::toBinary(ByteBuffer* out) const {
	out->putLong(this->maxTransactionId);
	out->putLong(this->maxObjectId);
	out->putLong(this->maxSchemaObjectId);

	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		Schema* schema = this->list.get(i);

		schema->toBinary(out);
	}
}

void SchemaRoot::fromBinary(ByteBuffer* in) {
	this->maxTransactionId = in->getLong();
	this->maxObjectId = in->getLong();
	this->maxSchemaObjectId = in->getLong();

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CdbBinaryObject* obj = TableObjectFactory::createFromBinary(in, Schema::CDB_OBJ_TYPE);
		Schema* schema = dynamic_cast<Schema*>(obj);

		schema->fromBinary(in);

		this->list.addElement(schema);
	}
}

uint64_t SchemaRoot::newTransactionId() noexcept {
	this->maxTransactionId++;
	return this->maxTransactionId;
}

uint64_t SchemaRoot::newSchemaObjectId() noexcept {
	this->maxSchemaObjectId++;
	return this->maxSchemaObjectId;
}

void SchemaRoot::createTable(CdbTable* table) {

}

} /* namespace codablecash */
