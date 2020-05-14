/*
 * SchemaObjectIdPublisher.cpp
 *
 *  Created on: 2020/05/14
 *      Author: iizuka
 */

#include "transaction/SchemaObjectIdPublisher.h"

#include "schema/Schema.h"

namespace codablecash {

SchemaObjectIdPublisher::SchemaObjectIdPublisher(Schema* schema) {
	this->schema = schema;
}

SchemaObjectIdPublisher::~SchemaObjectIdPublisher() {
	this->schema = nullptr;
}

uint64_t SchemaObjectIdPublisher::newOid() {
	return this->schema->newSchemaObjectId();
}


} /* namespace codablecash */
