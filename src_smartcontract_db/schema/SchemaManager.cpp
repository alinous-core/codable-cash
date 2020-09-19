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
#include "schema/ColumnModifyContext.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "base_io/File.h"
#include "base_io/ByteBuffer.h"

#include "base_io_stream/FileOutputStream.h"
#include "base_io_stream/FileInputStream.h"

#include "engine/CdbException.h"

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"

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


namespace codablecash {

const UnicodeString SchemaManager::PUBLIC(L"public");
const UnicodeString SchemaManager::SCHEMA_FILE(L"schema.bin");


SchemaManager::SchemaManager() {
	this->root = nullptr;
	this->schemaBin = nullptr;
	this->databaseBaseDir = nullptr;
}

SchemaManager::~SchemaManager() {
	delete this->root;
	delete this->schemaBin;
	delete this->databaseBaseDir;
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

void SchemaManager::handleAlterTableAddIndex(const AlterAddColumnCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);
}

void SchemaManager::handleAlterTableAddColumn(const AlterAddIndexCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);
}

void SchemaManager::handleAlterTableDropIndex(const AlterDropIndexCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);
}

void SchemaManager::handleAlterTableDropColumn(const AlterDropColumnCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);
}

void SchemaManager::handleAlterTableAddPrimaryKey(const AlterAddPrimaryKeyCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);
}

void SchemaManager::handleAlterTableDropPrimaryKey(const AlterDropPrimaryKeyCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);
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


	// TODO implement now
}

void SchemaManager::handleAlterTableRenameColumn(const AlterRenameColumnCommandLog* cmd) {
}

void SchemaManager::handleAlterTableRenameTable(const AlterRenameTableCommandLog* cmd) {
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

} /* namespace alinous */
