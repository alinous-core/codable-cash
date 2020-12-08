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

#include "scan_select/scan_condition/base/IValueProvider.h"

namespace codablecash {

SingleColumnIndex::SingleColumnIndex() {
	this->column = nullptr;
	this->topEq = false;
	this->topValue = nullptr;
	this->bottomEq = false;
	this->value = nullptr;

	this->range = false;
}

SingleColumnIndex::~SingleColumnIndex() {
	this->column = nullptr;
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

const UnicodeString* SingleColumnIndex::toCodeString() noexcept {
	if(this->str == nullptr){
		if(isRange()){
			makeRangeString();
		}
		else {
			makeString();
		}
	}

	return str;
}

void SingleColumnIndex::makeRangeString() noexcept {
	this->str = new UnicodeString(L"");

	if(this->value != nullptr){
		IValueProvider* vp = const_cast<IValueProvider*>(this->value);
		const UnicodeString* bottomStr = vp->toStringCode();
		this->str->append(bottomStr);

		this->str->append(L" <");
		if(isBottomEq()){
			this->str->append(L" =");
		}
		this->str->append(L" ");
	}

	const UnicodeString* colStr = this->column->getName();
	this->str->append(colStr);

	if(this->topValue != nullptr){
		this->str->append(L" <");
		if(isTopEq()){
			this->str->append(L" =");
		}
		this->str->append(L" ");

		IValueProvider* vp = const_cast<IValueProvider*>(this->topValue);
		const UnicodeString* topStr = vp->toStringCode();
		this->str->append(topStr);
	}
}

void SingleColumnIndex::makeString() noexcept {
	this->str = new UnicodeString(L"");

	const UnicodeString* colStr = this->column->getName();
	this->str->append(colStr);

	this->str->append(L" = ");

	IValueProvider* vp = const_cast<IValueProvider*>(this->topValue);
	const UnicodeString* valStr = vp->toStringCode();
	this->str->append(valStr);
}

} /* namespace codablecash */
