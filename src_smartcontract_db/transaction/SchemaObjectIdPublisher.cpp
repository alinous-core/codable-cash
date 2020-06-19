/*
 * SchemaObjectIdPublisher.cpp
 *
 *  Created on: 2020/05/14
 *      Author: iizuka
 */

#include "transaction/SchemaObjectIdPublisher.h"

#include "schema/SchemaManager.h"

namespace codablecash {

SchemaObjectIdPublisher::SchemaObjectIdPublisher(SchemaManager* schema) {
	this->schema = schema;
}

SchemaObjectIdPublisher::~SchemaObjectIdPublisher() {
	this->schema = nullptr;
}

uint64_t SchemaObjectIdPublisher::newOid() {
	return this->schema->newSchemaObjectId();
}

void SchemaObjectIdPublisher::saveSchema() {
	this->schema->save();
}

uint64_t SchemaObjectIdPublisher::getSchemaObjectVersionId() const noexcept {
	return this->schema->getSchemaObjectVersionId();
}

} /* namespace codablecash */
