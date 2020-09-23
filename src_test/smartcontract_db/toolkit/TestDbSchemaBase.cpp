/*
 * TestDbSchemaBase.cpp
 *
 *  Created on: 2020/08/24
 *      Author: iizuka
 */

#include "TestDbSchemaBase.h"

#include "engine/CodableDatabase.h"

#include "base_io/File.h"
#include "../../test_utils/TestEnv.h"
#include "vm/VirtualMachine.h"

#include "schema/SchemaManager.h"

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"
#include "table/CdbTableIndex.h"

#include "table_store/CdbStorageManager.h"
#include "table_store/TableStore.h"


namespace codablecash {

TestDbSchemaBase::TestDbSchemaBase(TestEnv* env) {
	this->env = env;
	this->dbDir = nullptr;
	this->vm = nullptr;
}

TestDbSchemaBase::~TestDbSchemaBase() {
	this->env = nullptr;
	delete this->dbDir;
	delete this->vm;
}

void TestDbSchemaBase::init() {
	init(1024 * 10);
}

void TestDbSchemaBase::init(uint64_t memCapacity) {
	this->vm = new VirtualMachine(memCapacity);

	createDb();

	this->vm->loadDatabase(this->dbDir);
}

CodableDatabase* TestDbSchemaBase::getDatabase() const noexcept {
	return this->vm->getDb();
}

void TestDbSchemaBase::createDb() {
	File testCaseFolder = this->env->testCaseDir();
	this->dbDir = testCaseFolder.get(L"db");
	{
		CodableDatabase db;
		db.createDatabase(this->dbDir);
	}
}

CdbTableColumn* TestDbSchemaBase::getColumn(const wchar_t* schema, const wchar_t* table, const wchar_t* column) {
	CdbTable* cdbtable = getTable(schema, table);

	CdbTableColumn* col = cdbtable->getColumn(column);

	return col;
}

CdbTableColumn* codablecash::TestDbSchemaBase::getColumn(const wchar_t* table, const wchar_t* column) {
	const wchar_t* s = SchemaManager::PUBLIC.towString();

	return getColumn(s, table, column);
}


CdbTable* TestDbSchemaBase::getTable(const wchar_t* schema, const wchar_t* table) {
	CodableDatabase* db = getDatabase();
	SchemaManager* scMgr = db->getSchemaManager();

	UnicodeString schemastr(schema);
	UnicodeString tableName(table);
	CdbTable* cdbtable = scMgr->getTable(&schemastr, &tableName);

	return cdbtable;
}

CdbTableIndex* TestDbSchemaBase::getIndex(const wchar_t* schema, const wchar_t* table, const wchar_t* column) {
	CodableDatabase* db = getDatabase();
	CdbStorageManager* storageMgr = db->getStorageManager();

	CdbTable* cdbtable = getTable(schema, table);

	CdbTableColumn* col = getColumn(schema, table, column);
	CdbTableIndex* index = cdbtable->getIndexByColumnOid(col->getOid());

	//TableStore* store = storageMgr->getTableStore(cdbtable->getOid());
	//CdbTableIndex* indexStore = store->getIndexStore(index->getOid());

	return index;
}

CdbTableIndex* codablecash::TestDbSchemaBase::getIndex(const wchar_t* table, const wchar_t* column) {
	const wchar_t* s = SchemaManager::PUBLIC.towString();

	return getIndex(s, table, column);
}

IndexStore* TestDbSchemaBase::getIndexStore(const wchar_t* table, const wchar_t* column) {
	const wchar_t* s = SchemaManager::PUBLIC.towString();

	return getIndexStore(s, table, column);
}

IndexStore* TestDbSchemaBase::getIndexStore(const wchar_t* schema, const wchar_t* table, const wchar_t* column) {
	CodableDatabase* db = getDatabase();
	CdbStorageManager* storageMgr = db->getStorageManager();

	CdbTable* cdbtable = getTable(schema, table);

	TableStore* store = storageMgr->getTableStore(cdbtable->getOid());

	CdbTableIndex* index = getIndex(schema, table, column);
	IndexStore* indexStore = store->getIndexStore(index->getOid());

	return indexStore;
}


} /* namespace codablecash */
