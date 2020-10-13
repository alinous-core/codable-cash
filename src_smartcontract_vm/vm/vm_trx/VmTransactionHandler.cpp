/*
 * VmTransactionHandler.cpp
 *
 *  Created on: 2020/05/24
 *      Author: iizuka
 */

#include "vm/vm_trx/VmTransactionHandler.h"
#include "vm/vm_trx/VmTransactionHandlerException.h"
#include "vm/vm_trx/StackTransactionReset.h"

#include "engine/CodableDatabase.h"

#include "trx/transaction/CdbTransaction.h"

#include "base/UnicodeString.h"

#include "schema_table/table/CdbTable.h"

#include "schema_table/schema/SchemaManager.h"
#include "schema_table/schema/Schema.h"

using codablecash::SchemaManager;

namespace alinous {

VmTransactionHandler::VmTransactionHandler(CodableDatabase* db) {
	this->db = db;
	this->trx = nullptr;
	this->currentSchema = new UnicodeString(&SchemaManager::PUBLIC);
}

VmTransactionHandler::~VmTransactionHandler() {
	reset();
	this->db = nullptr;
	delete this->currentSchema;
}

void VmTransactionHandler::begin() {
	if(this->trx != nullptr){
		throw new VmTransactionHandlerException(__FILE__, __LINE__);
	}

	this->trx = this->db->newTransaction();
}

void VmTransactionHandler::commit() {
	if(this->trx == nullptr){
		throw new VmTransactionHandlerException(__FILE__, __LINE__);
	}

	doCommit();
}


void VmTransactionHandler::rollback() {
	rollback(false);
}

void VmTransactionHandler::rollback(bool force) {
	if(!force && this->trx == nullptr){
		throw new VmTransactionHandlerException(__FILE__, __LINE__);
	}

	if(this->trx != nullptr){
		doRollback();
	}
}

void VmTransactionHandler::reset() noexcept {
	delete this->trx;
	this->trx = nullptr;
}

void VmTransactionHandler::doCommit() {
	StackTransactionReset resetter(this);

	this->trx->commit();
}

void VmTransactionHandler::createTable(CreateTableLog* cmd) {
	bool hasTrx = false;

	if(this->trx == nullptr){
		begin();
	}
	else{
		commit();
		begin();
		hasTrx = true;
	}

	this->trx->createTable(cmd);
	commit();

	if(hasTrx){
		begin();
	}
}

void VmTransactionHandler::dropTable(DropTableLog* cmd) {
	bool hasTrx = false;

	if(this->trx == nullptr){
		begin();
	}
	else{
		commit();
		begin();
		hasTrx = true;
	}

	this->trx->dropTable(cmd);
	commit();

	if(hasTrx){
		begin();
	}
}

void VmTransactionHandler::alterTable(AbstractAlterCommandLog* cmd) {
	bool hasTrx = false;

	if(this->trx == nullptr){
		begin();
	}
	else{
		commit();
		begin();
		hasTrx = true;
	}

	this->trx->alterTable(cmd);
	commit();

	if(hasTrx){
		begin();
	}
}

void VmTransactionHandler::doRollback() {
	StackTransactionReset resetter(this);

	this->trx->rollback();
}

void VmTransactionHandler::insert(InsertLog* cmd) {
	bool autoTrx = false;
	if(this->trx == nullptr){
		begin();
		autoTrx = true;
	}

	this->trx->insert(cmd);

	if(autoTrx){
		commit();
		autoTrx = false;
	}
}

uint64_t VmTransactionHandler::getSchemaObjectVersionId() const noexcept {
	return this->db->getSchemaObjectVersionId();
}

CdbTable* VmTransactionHandler::getTable(const UnicodeString* schema, const UnicodeString* tableName) const noexcept {
	SchemaManager* scManager = this->db->getSchemaManager();
	Schema* schemaObj = scManager->getSchema(schema);

	if(schemaObj == nullptr){
		return nullptr;
	}

	return schemaObj->getCdbTableByName(tableName);
}

} /* namespace alinous */
