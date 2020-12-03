/*
 * SingleColumnIndex.cpp
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index_resolv/SingleColumnIndex.h"

#include "schema_table/schema/SchemaManager.h"

#include "schema_table/table/CdbTableColumn.h"
#include "schema_table/table/CdbTable.h"

#include "scan_select/scan_table/TableScanTarget.h"

namespace codablecash {

SingleColumnIndex::SingleColumnIndex() {
	this->topEq = false;
	this->topValue = nullptr;
	this->bottomEq = false;
	this->value = nullptr;

	this->range = false;
}

SingleColumnIndex::~SingleColumnIndex() {
	this->topValue = nullptr;
	this->value = nullptr;
}

int SingleColumnIndex::size() const noexcept {
	return 1;
}

bool SingleColumnIndex::isRange() const noexcept {
	return this->range;
}

void SingleColumnIndex::setRange(bool range) noexcept {
	this->range = range;
}

bool SingleColumnIndex::hasIndex(SchemaManager* schemaManager) {
	const TableScanTarget* tableTarget = dynamic_cast<const TableScanTarget*>(this->target);
	const CdbTable* cdbTable = tableTarget->getTable();

	const CdbOid* columnOid = this->column->getOid();
	this->index = cdbTable->getIndexByColumnOid(columnOid);

	return this->index != nullptr;
}


} /* namespace codablecash */
