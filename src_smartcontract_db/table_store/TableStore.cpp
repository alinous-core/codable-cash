/*
 * TableStore.cpp
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#include "table_store/TableStore.h"
#include "table_store/RecordStore.h"

#include "base_io/File.h"

#include "table/CdbTable.h"

#include "schema/Schema.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"


namespace codablecash {

TableStore::TableStore(const File* baseDir, const CdbTable* table) {
	this->baseDir = new File(*baseDir);
	this->table = table;

	this->recordStore = nullptr;
}

TableStore::~TableStore() {
	delete this->baseDir;

	delete this->recordStore;
	this->table = nullptr;
}

const CdbOid* TableStore::getOid() const noexcept {
	return this->table->getOid();
}

void TableStore::createTable() {
	const Schema* schema = this->table->getSchema();
	const UnicodeString* schemaName = schema->getName();
	const UnicodeString* tableName = this->table->getName();

	File* schemaDir = this->baseDir->get(schemaName); __STP(schemaDir);
	File* tableDir = schemaDir->get(tableName);

	tableDir->deleteDir();
	tableDir->mkdirs();
}

void TableStore::loadTable() {
}


} /* namespace codablecash */
