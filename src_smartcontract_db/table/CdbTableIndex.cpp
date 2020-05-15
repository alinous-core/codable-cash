/*
 * CdbTableIndex.cpp
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#include "table/CdbTableIndex.h"
#include "table/CdbTableColumn.h"

#include "engine/CdbOid.h"

#include "transaction/SchemaObjectIdPublisher.h"

namespace codablecash {

CdbTableIndex::CdbTableIndex(uint64_t oid) {
	this->oid = new CdbOid(oid);
	this->columns = new ArrayList<CdbTableColumn>();
	this->columnMap = new HashMap<CdbOid, CdbTableColumn>();
	this->primary = false;
}

CdbTableIndex::~CdbTableIndex() {
	delete this->oid;
	delete this->columns;
	delete this->columnMap;
}

void CdbTableIndex::assignNewOid(SchemaObjectIdPublisher* publisher) {
	uint64_t oid = publisher->newOid();
	setOid(oid);
}

void CdbTableIndex::setOid(uint64_t oid) noexcept {
	delete this->oid;
	this->oid = new CdbOid(oid);
}

void CdbTableIndex::addColumn(CdbTableColumn* col) noexcept {
	this->columns->addElement(col);
	const CdbOid* o = col->getOid();
	this->columnMap->put(o, col);
}


bool CdbTableIndex::hasColumnOid(const CdbOid* colOid) const noexcept {
	return this->columnMap->get(colOid) != nullptr;
}


void CdbTableIndex::setPrimaryKey(bool bl) {
	this->primary = bl;
}

bool CdbTableIndex::isPrimaryKey() const noexcept {
	return this->primary;
}

} /* namespace codablecash */
