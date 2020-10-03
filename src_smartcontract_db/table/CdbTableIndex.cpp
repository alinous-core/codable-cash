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
	this->unique = inst.unique;
	this->name = new UnicodeString(inst.name);
}

CdbTableIndex::CdbTableIndex(uint64_t oid) {
	this->oid = new CdbOid(oid);
	this->columns = new ArrayList<CdbTableColumn>();
	this->columnMap = new HashMap<CdbOid, CdbTableColumn>();
	this->primary = false;
	this->unique = false;
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

UnicodeString* CdbTableIndex::createUniqueKeyIndexName(CdbTable* table, const UnicodeString* colName) noexcept {
	UnicodeString* newName = new UnicodeString(L"idx_unique_");

	const UnicodeString* tableName = table->getName();
	newName->append(tableName);

	newName->append(L"_");
	newName->append(colName);

	return newName;
}

void CdbTableIndex::setName(UnicodeString* name) noexcept {
	this->name = name;
}

void CdbTableIndex::assignNewOid(SchemaObjectIdPublisher* publisher) {
	uint64_t oid = publisher->newOid();
	setOid(oid);
}

void CdbTableIndex::syncColumnOid(const CdbTable* table) {
	int maxLoop = this->columns->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* idxcol = this->columns->get(i);
		const UnicodeString* name = idxcol->getName();

		CdbTableColumn* tablecol = table->getColumn(name);
		idxcol->setOid(tablecol->getOid()->getOidValue());

		this->columnMap->put(idxcol->getOid(), idxcol);
	}
}

void CdbTableIndex::setOid(uint64_t oid) noexcept {
	delete this->oid;
	this->oid = new CdbOid(oid);
}

void CdbTableIndex::addColumn(const CdbTableColumn* col) noexcept {
	CdbTableColumn* newColumn = new CdbTableColumn(*col);
	this->columns->addElement(newColumn);

	const CdbOid* o = newColumn->getOid();
	if(o->getOidValue() != 0){
		this->columnMap->put(o, newColumn);
	}
}


bool CdbTableIndex::hasColumnOid(const CdbOid* colOid) const noexcept {
	return this->columnMap->get(colOid) != nullptr;
}

int CdbTableIndex::getColumnLength() const noexcept {
	return this->columns->size();
}

void CdbTableIndex::setPrimaryKey(bool bl) {
	this->primary = bl;
}

bool CdbTableIndex::isPrimaryKey() const noexcept {
	return this->primary;
}

void CdbTableIndex::setUnique(bool unique) noexcept {
	this->unique = unique;
}

bool CdbTableIndex::isUnique() const noexcept {
	return this->unique;
}


int CdbTableIndex::binarySize() const {
	int total = sizeof(uint8_t);
	total += sizeof(uint64_t); // oid

	total += sizeof(uint8_t) * 2; // primary unique

	int maxLoop = this->columns->size();
	total += sizeof(int32_t);

	total += maxLoop * sizeof(uint64_t);

	return total;
}

void CdbTableIndex::toBinary(ByteBuffer* out) const {
	out->put(CdbTableIndex::CDB_OBJ_TYPE);
	out->putLong(this->oid->getOidValue());

	out->put(this->primary ? 1 : 0);// primary
	out->put(this->unique ? 1 : 0);// unique

	int maxLoop = this->columns->size();
	out->putInt(maxLoop);
	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* col = this->columns->get(i);
		const CdbOid* oid = col->getOid();
		uint64_t id = oid->getOidValue();

		out->putLong(id);
	}
}

void CdbTableIndex::fromBinary(ByteBuffer* in, CdbTable* table) {
	this->primary = in->get() > 0;
	this->unique = in->get() > 0;

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		uint64_t id = in->getLong();
		CdbOid oid(id);
		CdbTableColumn* col = table->findColumnByOid(&oid);

		checkNotNull(col);

		addColumn(col);
	}
}

void CdbTableIndex::adjustIndexColumnPosition(const CdbTable* table) noexcept {
	int maxLoop = this->columns->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* col = this->columns->get(i);

		const UnicodeString* name = col->getName();
		CdbTableColumn* tcol = table->getColumn(name);

		int position = tcol->getPosition();
		col->setPosition(position);
	}
}


const CdbOid* CdbTableIndex::getColumnOidAt(int idxColumnPos) const noexcept {
	CdbTableColumn* tcol = this->columns->get(idxColumnPos);

	return tcol->getOid();
}


} /* namespace codablecash */
