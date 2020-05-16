/*>s
 * CdbTable.cpp
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"

#include "engine/CdbOid.h"
#include "engine/CdbException.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "base_io/ByteBuffer.h"

#include "transaction/SchemaObjectIdPublisher.h"

#include "table/TableObjectFactory.h"
#include "table/CdbTableIndex.h"


namespace codablecash {

CdbTable::CdbTable(uint64_t oid) {
	this->columns = new ArrayList<CdbTableColumn>();
	this->columnMap = new HashMap<CdbOid, CdbTableColumn>();
	this->oid = new CdbOid(oid);
	this->name = nullptr;
	this->indexes = new ArrayList<CdbTableIndex>();
}

CdbTable::~CdbTable() {
	delete this->columnMap;

	this->columns->deleteElements();
	delete this->columns;
	delete this->oid;
	delete this->name;

	this->indexes->deleteElements();
	delete this->indexes;
}

void CdbTable::addColumn(uint8_t oid, const wchar_t* name,
		uint8_t type, int length, bool notnull, bool unique, const wchar_t* defaultValue) noexcept {
	UnicodeString strName(name);
	UnicodeString* strDefaultValue = nullptr;

	if(defaultValue != nullptr){
		strDefaultValue = new UnicodeString(defaultValue); __STP(strDefaultValue);
		addColumn(oid, &strName, type, length, notnull, unique, strDefaultValue);
		return;
	}

	addColumn(oid, &strName, type, length, notnull, unique, strDefaultValue);
}

void CdbTable::addColumn(uint8_t oid, const UnicodeString* name, uint8_t type, int length,
		bool notnull, bool unique, const UnicodeString* defaultValue) noexcept {
	CdbTableColumn* col = new CdbTableColumn(oid);
	col->setName(name);
	col->setType(type, length);
	col->setAttributes(notnull, unique);
	col->setDefaultValue(defaultValue);

	addColumn(col);
}

void CdbTable::addColumn(CdbTableColumn* col) noexcept {
	this->columns->addElement(col);
	const CdbOid* o = col->getOid();
	this->columnMap->put(o, col);
}

CdbTableColumn* CdbTable::getColumn(const wchar_t* name) noexcept {
	UnicodeString str(name);
	return getColumn(&str);
}

CdbTableColumn* CdbTable::getColumn(const UnicodeString* name) noexcept {
	CdbTableColumn* retcol = nullptr;

	int maxLoop = this->columns->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* col = this->columns->get(i);

		const UnicodeString* colname = col->getName();
		if(colname->equals(name)){
			retcol = col;
			break;
		}
	}

	return retcol;
}

CdbTableColumn* CdbTable::findColumnByOid(const CdbOid* oid) const noexcept {
	return this->columnMap->get(oid);
}

void CdbTable::assignNewOid(SchemaObjectIdPublisher* publisher) {
	uint64_t oid = publisher->newOid();
	setOid(oid);

	int maxLoop = this->columns->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* col = this->columns->get(i);

		col->assignNewOid(publisher);
	}

	maxLoop = this->indexes->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableIndex* idx = this->indexes->get(i);

		idx->assignNewOid(publisher);
	}

	publisher->saveSchema();
}

void CdbTable::setOid(uint64_t oid) noexcept {
	delete this->oid;
	this->oid = new CdbOid(oid);
}

void CdbTable::setName(UnicodeString* name) noexcept {
	this->name = name;
}


void CdbTable::setPrimaryKey(const wchar_t* col) {
	UnicodeString str(col);
	setPrimaryKey(&str);
}

void CdbTable::setPrimaryKey(const UnicodeString* colstr) {
	ArrayList<const UnicodeString> cols;
	cols.addElement(colstr);

	setPrimaryKeys(&cols);
}

void CdbTable::setPrimaryKeys(ArrayList<const UnicodeString>* cols) {
	ArrayList<CdbTableColumn> list;

	int maxLoop = cols->size();
	for(int i = 0; i != maxLoop; ++i){
		const UnicodeString* c = cols->get(i);
		CdbTableColumn* col = getColumn(c);

		if(col == nullptr){
			throw new CdbException(L"Column for primary key does not exists.", __FILE__, __LINE__);
		}

		list.addElement(col);
	}

	CdbTableIndex* index = new CdbTableIndex(0);
	addIndex(index);

	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* col = list.get(i);

		index->addColumn(col);
	}

	UnicodeString* indexName = CdbTableIndex::createPrimaryKeyIndexName(index, this);
	index->setName(indexName);
	index->setPrimaryKey(true);
}


void CdbTable::addIndex(CdbTableIndex* index) {
	this->indexes->addElement(index);
}

CdbTableIndex* CdbTable::getIndexByColumnOid(const CdbOid* oid) const noexcept {
	CdbTableIndex* ret = nullptr;

	int maxLoop = this->indexes->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableIndex* idx = this->indexes->get(i);

		if(idx->hasColumnOid(oid)){
			ret = idx;
			break;
		}
	}

	return ret;
}

int CdbTable::binarySize() const {
	checkNotNull(this->name);

	int total = sizeof(uint8_t);

	total += sizeof(uint64_t); // oid

	total += stringSize(this->name);

	int maxLoop = this->columns->size();
	total += sizeof(int32_t);
	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* col = this->columns->get(i);

		total += col->binarySize();
	}

	maxLoop = this->indexes->size();
	total += sizeof(int32_t);
	for(int i = 0; i != maxLoop; ++i){
		CdbTableIndex* idx = this->indexes->get(i);

		total += idx->binarySize();
	}

	return total;
}

void CdbTable::toBinary(ByteBuffer* out) const {
	checkNotNull(this->name);

	out->put(CdbTable::CDB_OBJ_TYPE);

	out->putLong(this->oid->getOid());

	putString(out, this->name);

	int maxLoop = this->columns->size();
	out->putInt(maxLoop);
	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* col = this->columns->get(i);

		col->toBinary(out);
	}

	maxLoop = this->indexes->size();
	out->putInt(maxLoop);
	for(int i = 0; i != maxLoop; ++i){
		CdbTableIndex* idx = this->indexes->get(i);

		idx->toBinary(out);
	}
}

void CdbTable::fromBinary(ByteBuffer* in) {
	this->name = getString(in);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CdbBinaryObject* obj = TableObjectFactory::createFromBinary(in, CdbTableColumn::CDB_OBJ_TYPE);
		CdbTableColumn* col = dynamic_cast<CdbTableColumn*>(obj);
		col->fromBinary(in);

		addColumn(col);
	}

	maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CdbBinaryObject* obj = TableObjectFactory::createFromBinary(in, CdbTableIndex::CDB_OBJ_TYPE);
		CdbTableIndex* idx = dynamic_cast<CdbTableIndex*>(obj);

		idx->fromBinary(in, this);
		addIndex(idx);
	}
}

} /* namespace codablecash */
