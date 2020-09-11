/*
 * ScanResultFieldMetadata.cpp
 *
 *  Created on: 2020/06/14
 *      Author: iizuka
 */

#include "transaction_scan_result/ScanResultFieldMetadata.h"

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"

#include "base/UnicodeString.h"


namespace codablecash {

ScanResultFieldMetadata::ScanResultFieldMetadata(const ScanResultFieldMetadata& inst) {
	this->position = inst.position;

	this->table = inst.table;
	this->column = inst.column;
	this->asName = inst.asName != nullptr ? new UnicodeString(inst.asName) : nullptr;
	this->use = inst.use;
}

ScanResultFieldMetadata::ScanResultFieldMetadata(const CdbTable* table, const CdbTableColumn* column) {
	this->position = -1;

	this->table = table;
	this->column = column;
	this->asName = nullptr;
	this->use = true;
}

ScanResultFieldMetadata::~ScanResultFieldMetadata() {
	delete this->asName;
}

void ScanResultFieldMetadata::setPosition(int pos) noexcept {
	this->position = pos;
}

} /* namespace codablecash */
