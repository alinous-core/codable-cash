/*
 * ScanResultFieldMetadata.cpp
 *
 *  Created on: 2020/06/14
 *      Author: iizuka
 */

#include "trx/scan/transaction_scan_result/ScanResultFieldMetadata.h"

#include "scan_select/scan_condition/params/ColumnIdentifierScanParam.h"

#include "schema_table/table/CdbTable.h"
#include "schema_table/table/CdbTableColumn.h"

#include "base/UnicodeString.h"

#include "engine/CdbOid.h"

namespace codablecash {

ScanResultFieldMetadata::ScanResultFieldMetadata(const ScanResultFieldMetadata& inst) {
	this->position = inst.position;

	this->sourceTarget = inst.sourceTarget;
	this->column = inst.column;
	this->asName = inst.asName != nullptr ? new UnicodeString(inst.asName) : nullptr;
	this->use = inst.use;
}

ScanResultFieldMetadata::ScanResultFieldMetadata(const AbstractScanTableTarget* sourceTarget, const CdbTableColumn* column) {
	this->position = -1;

	this->sourceTarget = sourceTarget;
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

bool ScanResultFieldMetadata::match(ColumnIdentifierScanParam* scanColumnId) const noexcept {
	const AbstractScanTableTarget* sourceTarget = scanColumnId->getSourceTarget();

	if(this->sourceTarget != sourceTarget){
		return false;
	}

	// Database table column case
	const CdbTableColumn* col = scanColumnId->getCdbColumn();
	if(this->column != nullptr && col != nullptr){
		const CdbOid* thisOid = this->column->getOid();
		const CdbOid* colOid = col->getOid();

		return thisOid->equals(colOid);
	}

	// FIXME virtual column like subquery

	return false;
}

} /* namespace codablecash */
