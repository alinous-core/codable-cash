/*
 * CdbTableIndex.cpp
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#include "table/CdbTableIndex.h"
#include "table/CdbTableColumn.h"
#include "table/CdbTable.h"

#include "engine/CdbOid.h"

#include "transaction/SchemaObjectIdPublisher.h"

#include "base_io/ByteBuffer.h"


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

int CdbTableIndex::binarySize() const {
	int total = sizeof(uint8_t);
	total += sizeof(uint64_t); // oid

	int maxLoop = this->columns->size();
	total += sizeof(int32_t);

	total += maxLoop * sizeof(uint64_t);

	return total;
}

void CdbTableIndex::toBinary(ByteBuffer* out) const {
	out->put(CdbTableColumn::CDB_OBJ_TYPE);
	out->putLong(this->oid->getOid());

	int maxLoop = this->columns->size();
	out->putInt(maxLoop);
	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* col = this->columns->get(i);
		const CdbOid* oid = col->getOid();
		uint64_t id = oid->getOid();

		out->putLong(id);
	}
}

void CdbTableIndex::fromBinary(ByteBuffer* in, CdbTable* table) {
	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		uint64_t id = in->getLong();
		CdbOid oid(id);
		CdbTableColumn* col = table->findColumnByOid(&oid);

		checkNotNull(col);

		addColumn(col);
	}
}


} /* namespace codablecash */
