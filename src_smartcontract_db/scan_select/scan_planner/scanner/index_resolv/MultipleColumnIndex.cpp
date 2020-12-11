/*
 * MultipleColumnIndex.cpp
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index_resolv/MultipleColumnIndex.h"
#include "scan_select/scan_planner/scanner/index_resolv/SingleColumnIndex.h"

#include "scan_select/scan_table/TableScanTarget.h"

#include "schema_table/table/CdbTable.h"
#include "schema_table/table/CdbTableColumn.h"

#include "base/ArrayList.h"
#include "base/UnicodeString.h"

#include "engine/CdbOid.h"

namespace codablecash {

MultipleColumnIndex::MultipleColumnIndex(const MultipleColumnIndex& inst) : AbstractColumnsIndexWrapper(inst) {
	int maxLoop = inst.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractColumnsIndexWrapper* index = inst.list.get(i);
		SingleColumnIndex* idx = dynamic_cast<SingleColumnIndex*>(index->clone());

		assert(idx != nullptr);

		add(idx);
	}
}

MultipleColumnIndex::MultipleColumnIndex() {

}

MultipleColumnIndex::~MultipleColumnIndex() {
	this->list.deleteElements();
}

bool MultipleColumnIndex::hasIndex(SchemaManager* schemaManager) {
	const TableScanTarget* tableTarget = dynamic_cast<const TableScanTarget*>(this->target);
	const CdbTable* cdbTable = tableTarget->getTable();

	ArrayList<const CdbOid> oidlist;

	int maxLoop = size();
	for(int i = 0; i != maxLoop; ++i){
		SingleColumnIndex* idx = this->list.get(i);

		const CdbTableColumn* col = idx->getColumn();
		const CdbOid* oid = col->getOid();

		oidlist.addElement(oid);
	}

	this->index = cdbTable->findMostAvailableIndex(&oidlist);

	return this->index != nullptr;
}

int MultipleColumnIndex::size() const noexcept {
	return this->list.size();
}

void MultipleColumnIndex::add(SingleColumnIndex* idx) noexcept {
	this->list.addElement(idx);
}

const UnicodeString* MultipleColumnIndex::toCodeString() noexcept {
	if(this->str == nullptr){
		makeCodeString();
	}

	return this->str;
}

void MultipleColumnIndex::makeCodeString() noexcept {
	this->str = new UnicodeString(L"");

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		SingleColumnIndex* index = this->list.get(i);

		if(i != 0){
			this->str->append(L" AND ");
		}

		const UnicodeString* s = index->toCodeString();
		this->str->append(s);
	}
}

AbstractColumnsIndexWrapper* MultipleColumnIndex::clone() const noexcept {
	return new MultipleColumnIndex(*this);
}


} /* namespace codablecash */
