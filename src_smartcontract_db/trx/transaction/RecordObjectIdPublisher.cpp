/*
 * RecordObjectIdPublisher.cpp
 *
 *  Created on: 2020/05/29
 *      Author: iizuka
 */

#include "trx/transaction/RecordObjectIdPublisher.h"

#include "schema_table/schema/SchemaManager.h"


namespace codablecash {

RecordObjectIdPublisher::RecordObjectIdPublisher(SchemaManager* schema) {
	this->schema = schema;
}

RecordObjectIdPublisher::~RecordObjectIdPublisher() {
	this->schema = nullptr;
}

uint64_t RecordObjectIdPublisher::newOid() noexcept {
	return this->schema->newRecordObjectId();
}

void RecordObjectIdPublisher::saveSchema() {
	this->schema->save();
}

} /* namespace codablecash */
