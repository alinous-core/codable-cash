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
#include "table/ColumnIndexMatcher.h"

#include "schema/SchemaManager.h"

#include "transaction_scan_result/ScanResultMetadata.h"

#include "transaction_scan_result/ScanResultFieldMetadata.h"

using namespace alinous;

namespace codablecash {

CdbTable::CdbTable(const CdbTable& inst) {
	this->oid = new CdbOid(*inst.oid);

	this->schemaName = new UnicodeString(inst.schemaName);
	this->name = new UnicodeString(inst.name);

	this->columns = new ArrayList<CdbTableColumn>();
	this->columnMap = new HashMap<CdbOid, CdbTableColumn>();
	{
		int maxLoop = inst.columns->size();
		for(int i = 0; i != maxLoop; ++i){
			CdbTableColumn* col = inst.columns->get(i);

			addColumn(new CdbTableColumn(*col));
		}
	}

	this->indexes = new ArrayList<CdbTableIndex>();
	{
		int maxLoop = inst.indexes->size();
		for(int i = 0; i != maxLoop; ++i){
			CdbTableIndex* idx = inst.indexes->get(i);

			addIndex(new CdbTableIndex(*idx));
		}
	}
	this->parent = nullptr;

	this->fqn = nullptr;
}


CdbTable::CdbTable(uint64_t oid) {
	this->columns = new ArrayList<CdbTableColumn>();
	this->columnMap = new HashMap<CdbOid, CdbTableColumn>();
	this->oid = new CdbOid(oid);
	this->schemaName = new UnicodeString(&SchemaManager::PUBLIC);
	this->name = nullptr;
	this->indexes = new ArrayList<CdbTableIndex>();
	this->parent = nullptr;
	this->fqn = nullptr;
}

CdbTable::~CdbTable() {
	delete this->columnMap;

	this->columns->deleteElements();
	delete this->columns;
	delete this->oid;
	delete this->name;
	delete this->schemaName;

	this->indexes->deleteElements();
	delete this->indexes;

	this->schemaName = nullptr;
	delete this->fqn;
}
void CdbTable::setSchemaName(UnicodeString* schemaName) noexcept {
	delete this->schemaName;
	this->schemaName = schemaName;
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
	int position = this->columns->size();
	col->setPosition(position);

	this->columns->addElement(col);
	const CdbOid* o = col->getOid();
	this->columnMap->put(o, col);
}

CdbTableColumn* CdbTable::getColumn(const wchar_t* name) noexcept {
	UnicodeString str(name);
	return getColumn(&str);
}

CdbTableColumn* CdbTable::getColumn(const UnicodeString* name) const noexcept {
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

CdbTableColumn* CdbTable::getColumn(int index) const noexcept {
	return this->columns->get(index);
}

CdbTableColumn* CdbTable::findColumnByOid(const CdbOid* oid) const noexcept {
	return this->columnMap->get(oid);
}

const ArrayList<CdbTableColumn>* CdbTable::getColumns() const noexcept {
	return this->columns;
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

		// assign to column
		idx->syncColumnOid(this);
	}

	setupUniqueIndexes();

	maxLoop = this->indexes->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableIndex* idx = this->indexes->get(i);

		idx->assignNewOid(publisher);

		// assign to column
		idx->syncColumnOid(this);
	}

	publisher->saveSchema();
}


void CdbTable::setupUniqueIndexes() {
	int maxLoop = this->columns->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* col = this->columns->get(i);

		const CdbOid* colOid = col->getOid();
		bool unique = col->isUnique();

		// unique index
		if(unique && !hasSinglePrimaryKeyColumn(colOid)){
			CdbTableIndex* index = new CdbTableIndex((uint64_t)0);
			index->addColumn(col);

			UnicodeString* indexName = CdbTableIndex::createUniqueKeyIndexName(this, name);
			index->setName(indexName);
			index->setUnique(true);

			addIndex(index);
		}
	}
}

void CdbTable::setOid(uint64_t oid) noexcept {
	delete this->oid;
	this->oid = new CdbOid(oid);
}

void CdbTable::setName(UnicodeString* name) noexcept {
	delete  this->name;
	this->name = name;
}


void CdbTable::setPrimaryKey(const wchar_t* col) {
	UnicodeString str(col);
	setPrimaryKey(&str);
}

void CdbTable::setPrimaryKey(const UnicodeString* colstr) {
	ArrayList<UnicodeString> cols;
	cols.setDeleteOnExit();

	cols.addElement(new UnicodeString(colstr));

	setPrimaryKeys(&cols);
}

const CdbTableIndex* CdbTable::setPrimaryKeys(const ArrayList<UnicodeString>* cols) {
	ArrayList<CdbTableColumn> list;
	ArrayList<const CdbOid> oidlist;

	int maxLoop = cols->size();
	for(int i = 0; i != maxLoop; ++i){
		const UnicodeString* c = cols->get(i);
		CdbTableColumn* col = getColumn(c);

		if(col == nullptr){
			throw new CdbException(L"Column for primary key does not exists.", __FILE__, __LINE__);
		}

		list.addElement(col);

		const CdbOid* oid = col->getOid();
		oidlist.addElement(oid);
	}

	CdbTableIndex* prevIndex = getIndexByColumnOidsStrict(&oidlist, true);
	if(prevIndex != nullptr){
		prevIndex->setPrimaryKey(true);

		return nullptr;
	}

	CdbTableIndex* index = new CdbTableIndex((uint64_t)0);
	index->setUnique(true);
	addIndex(index);

	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* col = list.get(i);

		index->addColumn(col);
	}

	UnicodeString* indexName = CdbTableIndex::createPrimaryKeyIndexName(index, this);
	index->setName(indexName);
	index->setPrimaryKey(true);

	adjustIndexColumnPosition();

	return index;
}

CdbTableIndex* CdbTable::getPrimaryKey() const noexcept {
	CdbTableIndex* ret = nullptr;

	int maxLoop = this->indexes->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableIndex* idx = this->indexes->get(i);

		if(idx->isPrimaryKey()){
			ret = idx;
			break;
		}
	}

	return ret;
}

bool CdbTable::hasSinglePrimaryKeyColumn(const CdbOid* columnOid) const noexcept {
	bool ret = false;

	int maxLoop = this->indexes->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableIndex* idx = this->indexes->get(i);

		if(idx->isPrimaryKey() && idx->getColumnLength() == 1 && idx->hasColumnOid(columnOid)){
			ret = true;
			break;
		}
	}

	return ret;
}

void CdbTable::addIndex(CdbTableIndex* index) {
	this->indexes->addElement(index);

	adjustIndexColumnPosition();
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


CdbTableIndex* CdbTable::getIndexByColumnOids(const ArrayList<const CdbOid>* oidlist) const noexcept {
	ColumnIndexMatcher* matcher = nullptr;

	int maxLoop = this->indexes->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableIndex* idx = this->indexes->get(i);


		ColumnIndexMatcher* current = new ColumnIndexMatcher(idx);
		StackRelease<ColumnIndexMatcher> st_current(current);

		current->doMatch(oidlist);

		int length = current->getLength();
		if(length != 0 && (matcher == nullptr || matcher->getLength() < length)){
			delete matcher;
			matcher = current;
			st_current.cancel();
		}
	}

	CdbTableIndex* ret = matcher != nullptr ? matcher->getIdx(): nullptr;
	delete matcher;

	return ret;
}


CdbTableIndex* CdbTable::getIndexByColumnOidsStrict(const ArrayList<const CdbOid>* oidlist, bool uniqueData) const noexcept {
	CdbTableIndex* ret = nullptr;
	int keyLength = oidlist->size();

	int maxLoop = this->indexes->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableIndex* idx = this->indexes->get(i);

		if(idx->isUniqueDataRequired() != uniqueData){
			continue;
		}

		int l = idx->getColumnLength();
		if(l != keyLength){
			continue;
		}

		bool hit = true;
		for(int j = 0; j != keyLength; ++j){
			const CdbOid* oid = oidlist->get(j);
			const CdbOid* oidIdxCol = idx->getColumnOidAt(j);

			if(!oid->equals(oidIdxCol)){
				hit = false;
				break;
			}
		}

		if(hit){
			ret = idx;
			break;
		}
	}

	return ret;
}

void CdbTable::removeIndex(const CdbTableIndex* ptr) noexcept {
	int removeIndex = -1;

	int maxLoop = this->indexes->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableIndex* idx = this->indexes->get(i);

		if(idx == ptr){
			removeIndex = i;
			break;
		}
	}

	if(removeIndex >= 0){
		this->indexes->remove(removeIndex);
	}
}

void CdbTable::renameColumn(const UnicodeString* lastColumn, const UnicodeString* newColumn) {
	CdbTableColumn* column = getColumn(lastColumn);
	column->setName(newColumn);

	const CdbOid* columnOid = column->getOid();

	int maxLoop = this->indexes->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableIndex* idx = this->indexes->get(i);

		idx->renameColumn(columnOid, newColumn);
	}
}


int CdbTable::binarySize() const {
	checkNotNull(this->schemaName);
	checkNotNull(this->name);

	int total = sizeof(uint8_t);

	total += sizeof(uint64_t); // oid

	total += stringSize(this->schemaName);
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
	checkNotNull(this->schemaName);
	checkNotNull(this->name);

	out->put(CdbTable::CDB_OBJ_TYPE);

	out->putLong(this->oid->getOidValue());

	putString(out, this->schemaName);
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
	delete this->schemaName;
	this->schemaName = getString(in);
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

	adjustIndexColumnPosition();
}

void CdbTable::setSchema(Schema* schema) noexcept {
	this->parent = schema;
}

const Schema* CdbTable::getSchema() const noexcept {
	return this->parent;
}

const UnicodeString* CdbTable::getTableFqn() noexcept {
	if(this->fqn == nullptr){
		this->fqn = new UnicodeString(this->schemaName);
		this->fqn->append(L".");
		this->fqn->append(this->name);
	}

	return this->fqn;
}


const ArrayList<CdbTableIndex>* CdbTable::getIndexes() const noexcept {
	return this->indexes;
}

void CdbTable::adjustIndexColumnPosition() noexcept {
	int maxLoop = this->columns->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* col = this->columns->get(i);
		col->setPosition(i);
	}

	maxLoop = this->indexes->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableIndex* index = this->indexes->get(i);

		index->adjustIndexColumnPosition(this);
	}

}

ScanResultMetadata* CdbTable::getMetadata() const noexcept {
	ScanResultMetadata* metadata = new ScanResultMetadata();

	int maxLoop = this->columns->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* col = this->columns->get(i);

		ScanResultFieldMetadata* fld = col->getFieldMetadata(this); __STP(fld);
		metadata->addField(fld);
	}

	return metadata;
}


} /* namespace codablecash */
