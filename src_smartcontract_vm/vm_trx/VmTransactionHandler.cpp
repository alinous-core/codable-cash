/*
 * VmTransactionHandler.cpp
 *
 *  Created on: 2020/05/24
 *      Author: iizuka
 */

#include "vm_trx/VmTransactionHandler.h"
#include "vm_trx/VmTransactionHandlerException.h"
#include "vm_trx/StackTransactionReset.h"

#include "engine/CodableDatabase.h"

#include "transaction/CdbTransaction.h"


namespace alinous {

VmTransactionHandler::VmTransactionHandler(CodableDatabase* db) {
	this->db = db;
	this->trx = nullptr;
}

VmTransactionHandler::~VmTransactionHandler() {
	this->db = nullptr;
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
	if(this->trx == nullptr){
		throw new VmTransactionHandlerException(__FILE__, __LINE__);
	}

	doRollback();
}

void VmTransactionHandler::reset() noexcept {
	delete this->trx;
	this->trx = nullptr;
}

void VmTransactionHandler::doCommit() {
	StackTransactionReset resetter(this);

	this->trx->commit();
}

void VmTransactionHandler::doRollback() {
	StackTransactionReset resetter(this);

	this->trx->rollback();
}

} /* namespace alinous */
