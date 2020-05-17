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

#include "base/UnicodeString.h"

namespace codablecash {

CdbTableIndex::CdbTableIndex(const CdbTableIndex& inst) {
	this->oid = new CdbOid(*inst.oid);

	this->columns = new ArrayList<CdbTableColumn>();
	this->columnMap = new HashMap<CdbOid, CdbTableColumn>();
	{
		int maxLoop = inst.columns->size();
		for(int i = 0; i != maxLoop; ++i){
			CdbTableColumn* col = inst.columns->get(i);

			addColumn(col);
		}
	}

	this->primary = inst.primary;
	this->name = new UnicodeString(inst.name);
}

CdbTableIndex::CdbTableIndex(uint64_t oid) {
	this->oid = new CdbOid(oid);
	this->columns = new ArrayList<CdbTableColumn>();
	this->columnMap = new HashMap<CdbOid, CdbTableColumn>();
	this->primary = false;
	this->name = nullptr;
}

CdbTableIndex::~CdbTableIndex() {
	delete this->oid;

	this->columns->deleteElements();
	delete this->columns;
	delete this->columnMap;

	delete this->name;
}

UnicodeString* CdbTableIndex::createPrimaryKeyIndexName(CdbTableIndex* index, CdbTable* table) noexcept {
	UnicodeString* newName = new UnicodeString(L"idx_");

	const UnicodeString* tableName = table->getName();
	newName->append(tableName);

	const ArrayList<CdbTableColumn>* list = index->getColumns();
	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* col = list->get(i);
		const UnicodeString*  colName = col->getName();

		newName->append(L"_");
		newName->append(colName);
	}

	return newName;
}

void CdbTableIndex::setName(UnicodeString* name) noexcept {
	this->name = name;
}

void CdbTableIndex::assignNewOid(SchemaObjectIdPublisher* publisher) {
	uint64_t oid = publisher->newOid();
	setOid(oid);
}

void CdbTableIndex::setOid(uint64_t oid) noexcept {
	delete this->oid;
	this->oid = new CdbOid(oid);
}

void CdbTableIndex::addColumn(const CdbTableColumn* col) noexcept {
	CdbTableColumn* newColumn = new CdbTableColumn(*col);
	this->columns->addElement(newColumn);
	const CdbOid* o = newColumn->getOid();
	this->columnMap->put(o, newColumn);
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

	total += sizeof(uint8_t); // primary

	int maxLoop = this->columns->size();
	total += sizeof(int32_t);

	total += maxLoop * sizeof(uint64_t);

	return total;
}

void CdbTableIndex::toBinary(ByteBuffer* out) const {
	out->put(CdbTableIndex::CDB_OBJ_TYPE);
	out->putLong(this->oid->getOid());

	out->put(this->primary ? 1 : 0);// primary

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
	this->primary = in->get() > 0;

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
