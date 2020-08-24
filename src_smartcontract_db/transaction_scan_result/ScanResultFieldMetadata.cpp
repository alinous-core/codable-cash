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

ScanResultFieldMetadata::ScanResultFieldMetadata() {
	this->position = -1;

	this->table = nullptr;
	this->column = nullptr;
	this->asName = nullptr;
	this->use = true;
}

ScanResultFieldMetadata::~ScanResultFieldMetadata() {
	delete this->table;
	delete this->column;
	delete this->asName;
}

} /* namespace codablecash */
