/*
 * Schema.cpp
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#include "schema/SchemaManager.h"
#include "schema/SchemaRoot.h"
#include "schema/ISchemaUptateListner.h"
#include "schema/Schema.h"

#include "schema_alter_ctx/ColumnModifyContext.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "base_io/File.h"
#include "base_io/ByteBuffer.h"

#include "base_io_stream/FileOutputStream.h"
#include "base_io_stream/FileInputStream.h"

#include "engine/CdbException.h"

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"
#include "table/CdbTableIndex.h"

#include "sql_ddl_alter_modify/AlterModifyCommand.h"

#include "transaction_log_alter_modify/AlterModifyCommandLog.h"

#include "sql_join_parts/TableIdentifier.h"

#include "transaction_log_alter/AlterAddColumnCommandLog.h"
#include "transaction_log_alter/AlterAddIndexCommandLog.h"
#include "transaction_log_alter/AlterDropIndexCommandLog.h"
#include "transaction_log_alter/AlterDropColumnCommandLog.h"
#include "transaction_log_alter_modify/AlterAddPrimaryKeyCommandLog.h"
#include "transaction_log_alter_modify/AlterDropPrimaryKeyCommandLog.h"
#include "transaction_log_alter_modify/AlterRenameColumnCommandLog.h"
#include "transaction_log_alter_modify/AlterRenameTableCommandLog.h"

#include "sql_ddl/DdlColumnDescriptor.h"
#include "sql_ddl/ColumnTypeDescriptor.h"

#include "schema/SchemaAlterCommandsHandler.h"

namespace codablecash {

const UnicodeString SchemaManager::PUBLIC(L"public");
const UnicodeString SchemaManager::SCHEMA_FILE(L"schema.bin");


SchemaManager::SchemaManager() {
	this->root = nullptr;
	this->schemaBin = nullptr;
	this->databaseBaseDir = nullptr;
	this->alterHandler = new SchemaAlterCommandsHandler();
}

SchemaManager::~SchemaManager() {
	delete this->root;
	this->root = nullptr;

	delete this->schemaBin;
	this->schemaBin = nullptr;

	delete this->databaseBaseDir;
	this->databaseBaseDir = nullptr;

	delete this->alterHandler;
	this->alterHandler = nullptr;
}

void SchemaManager::addSchemaUpdateListner(ISchemaUptateListner* listner) noexcept {
	this->listners.addElement(listner);
}

void SchemaManager::createSchema(const UnicodeString* name, File* baseDir) {
	SchemaRoot root;

	root.addSchemaName(&SchemaManager::PUBLIC);
	File* scdir = baseDir->get(&SchemaManager::PUBLIC); __STP(scdir);

	scdir->mkdirs();

	File* schemaBin = baseDir->get(&SchemaManager::SCHEMA_FILE); __STP(schemaBin);

	FileOutputStream* outStream = new FileOutputStream(schemaBin); __STP(outStream);
	outStream->open(false);

	int size = root.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	root.toBinary(buff);

	const uint8_t* barray = buff->array();
	outStream->write((const char*)barray, size);
	outStream->flush();

	outStream->close();
}

void SchemaManager::save() {
	FileOutputStream* outStream = new FileOutputStream(schemaBin); __STP(outStream);
	outStream->open(false);

	int size = this->root->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	this->root->toBinary(buff);

	const uint8_t* barray = buff->array();
	outStream->write((const char*)barray, size);
	outStream->flush();

	outStream->close();
}


void SchemaManager::loadSchema(const File* baseDir) {
	this->databaseBaseDir = new File(*baseDir);
	this->schemaBin = baseDir->get(&SchemaManager::SCHEMA_FILE);

	int size = schemaBin->length();
	char* b = new char[size]{};
	StackArrayRelease<char> br(b);

	FileInputStream* inStream = new FileInputStream(schemaBin); __STP(inStream);
	inStream->open();

	inStream->read(b, size);

	inStream->close();

	ByteBuffer* buff = ByteBuffer::wrapWithEndian((const uint8_t*)b, size, true); __STP(buff);

	this->root = new SchemaRoot();
	this->root->fromBinary(buff);

	fireSchemaLoaded();
}

uint64_t SchemaManager::newTransactionId() {
	uint64_t trxId = this->root->newTransactionId();
	save();

	return trxId;
}

uint64_t SchemaManager::newSchemaObjectId() noexcept {
	return this->root->newSchemaObjectId();
}

uint64_t SchemaManager::newRecordObjectId() noexcept {
	return this->root->newRecordObjectId();
}

uint64_t SchemaManager::getSchemaObjectVersionId() const noexcept {
	return this->root->getSchemaObjectVersionId();
}

void SchemaManager::createTable(CdbTable* table) {
	const CdbTable* newTable = this->root->createTable(table);
	fireOnCreateTable(newTable);

	save();
}

void SchemaManager::handleAlterTableAddIndex(const AlterAddIndexCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);

	// TODO: alter add

	// upgrade
	this->root->upgradeSchemaObjectVersionId();
	save();
}

void SchemaManager::handleAlterTableAddColumn(const AlterAddColumnCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);

	// upgrade
	this->root->upgradeSchemaObjectVersionId();
	save();
}

void SchemaManager::handleAlterTableDropIndex(const AlterDropIndexCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);

	// upgrade
	this->root->upgradeSchemaObjectVersionId();
	save();
}

void SchemaManager::handleAlterTableDropColumn(const AlterDropColumnCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);

	// upgrade
	this->root->upgradeSchemaObjectVersionId();
	save();
}

void SchemaManager::handleAlterTableAddPrimaryKey(const AlterAddPrimaryKeyCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);

	// upgrade
	this->root->upgradeSchemaObjectVersionId();
	save();
}

void SchemaManager::handleAlterTableDropPrimaryKey(const AlterDropPrimaryKeyCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);

	CdbTableIndex* primaryKey = table->getPrimaryKey(); __STP(primaryKey);
	if(primaryKey == nullptr){
		return;
	}

	table->removeIndex(primaryKey);

	fireOnDropPrimaryKey(table, primaryKey);


	// upgrade
	this->root->upgradeSchemaObjectVersionId();
	save();
}

void SchemaManager::handleAlterTableModify(const AlterModifyCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);

	const AlterModifyCommand* modifyCommand = cmd->getCommand();

	const DdlColumnDescriptor* newdesc = modifyCommand->getColumnDescriptor();

	CdbTableColumn* col = table->getColumn(newdesc->getName());
	if(col == nullptr){
		throw new CdbException(L"Column does not exists.", __FILE__, __LINE__);
	}

	const UnicodeString* defaultStr = cmd->getDefaultValueStr();

	ColumnModifyContext* context = col->createModifyContextwithChange(modifyCommand, defaultStr); __STP(context);
	context->setColumn(col);

	// convert default
	context->analyze();

	handleUniqueIndexOnModify(table, context);

	// update storage
	fireOnAlterModify(table, context);

	// upgrade
	this->root->upgradeSchemaObjectVersionId();
	save();
}

void SchemaManager::handleUniqueIndexOnModify(CdbTable* table, ColumnModifyContext* ctx) {
	ColumnModifyContext::UniqueChage change = ctx->getUniqueChange();

	if(change == ColumnModifyContext::UniqueChage::TO_NOT_UNIQUE){
		handleToNotUnique(table, ctx);
	}
	else if(change == ColumnModifyContext::UniqueChage::TO_UNIQUE){
		handleToUnique(table, ctx);
	}
}

void SchemaManager::handleToNotUnique(CdbTable* table, ColumnModifyContext* ctx) {
	CdbTableColumn* col = ctx->getColumn();
	const CdbOid* colOid = col->getOid();

	CdbTableIndex* index = table->getUniqueIndexByColumnOid(colOid);
	if(index == nullptr || index->isPrimaryKey()){ // primary key support unique
		return;
	}

	ctx->setRemovalIndex(index);
	table->removeIndex(index);
}

void SchemaManager::handleToUnique(CdbTable* table, ColumnModifyContext* ctx) {
	CdbTableColumn* col = ctx->getColumn();
	const CdbOid* colOid = col->getOid();

	// already has primary key
	if(table->hasSinglePrimaryKeyColumn(colOid)){
		return;
	}

	uint64_t newOid = this->root->newSchemaObjectId();
	CdbTableIndex* newIndex = new CdbTableIndex(newOid);
	ctx->setNewIndex(newIndex);

	UnicodeString* indexName = CdbTableIndex::createUniqueKeyIndexName(table, col->getName());
	newIndex->setName(indexName);
	newIndex->addColumn(col);
	newIndex->setUnique(true);

	table->addIndex(newIndex);
}

void SchemaManager::handleAlterTableRenameColumn(const AlterRenameColumnCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);

	// upgrade
	this->root->upgradeSchemaObjectVersionId();
	save();
}

void SchemaManager::handleAlterTableRenameTable(const AlterRenameTableCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);

	// upgrade
	this->root->upgradeSchemaObjectVersionId();
	save();
}


void SchemaManager::fireSchemaLoaded() noexcept {
	int maxLoop = this->listners.size();
	for(int i = 0; i != maxLoop; ++i){
		ISchemaUptateListner* l = this->listners.get(i);
		l->schemaLoaded(this);
	}
}

CdbTable* SchemaManager::findTableFromCommand(const AbstractAlterCommandLog* cmdlog) {
	const TableIdentifier* tableId = cmdlog->getTableId();

	const UnicodeString* schema = tableId->getSchema();
	const UnicodeString* tableName = tableId->getTableName();

	CdbTable* table = getTable(schema, tableName);

	return table;
}

Schema* SchemaManager::getSchema(const UnicodeString* name) const noexcept {
	return this->root->getSchema(name);
}

const ArrayList<Schema>* SchemaManager::getSchemaList() const noexcept {
	return this->root->getSchemaList();
}

CdbTable* SchemaManager::getTable(const wchar_t* schema, const wchar_t* name) const {
	UnicodeString s(schema);
	UnicodeString n(name);

	return getTable(&s, &n);
}

CdbTable* SchemaManager::getTable(const TableIdentifier* tableId, const UnicodeString* defaultSchema) const {
	const UnicodeString* schema = tableId->getSchema();
	const UnicodeString* table = tableId->getTableName();

	if(schema == nullptr){
		schema = defaultSchema;
	}

	return getTable(schema, table);
}


CdbTable* SchemaManager::getTable(const UnicodeString* schema, const UnicodeString* name) const {
	Schema* sc = getSchema(schema);
	if(sc == nullptr){
		throw new CdbException(L"schema does not exists.", __FILE__, __LINE__);
	}

	CdbTable* table = sc->getCdbTableByName(name);
	if(table == nullptr){
		throw new CdbException(L"schema does not exists.", __FILE__, __LINE__);
	}

	return table;
}


void SchemaManager::fireOnCreateTable(const CdbTable* table) {
	int maxLoop = this->listners.size();
	for(int i = 0; i != maxLoop; ++i){
		ISchemaUptateListner* l = this->listners.get(i);
		l->onCreateTable(this, table);
	}

}

void SchemaManager::fireOnAlterModify(const CdbTable* table, const ColumnModifyContext* ctx) {
	int maxLoop = this->listners.size();
	for(int i = 0; i != maxLoop; ++i){
		ISchemaUptateListner* l = this->listners.get(i);
		l->onAlterModify(this, table, ctx);
	}
}

void SchemaManager::fireOnDropPrimaryKey(const CdbTable* table, const CdbTableIndex* primaryKey) {
	int maxLoop = this->listners.size();
	for(int i = 0; i != maxLoop; ++i){
		ISchemaUptateListner* l = this->listners.get(i);
		l->onDropPrimaryKey(this, table, primaryKey);
	}
}


} /* namespace alinous */
