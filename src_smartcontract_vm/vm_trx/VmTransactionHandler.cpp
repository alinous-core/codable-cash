/*
 * VmTransactionHandler.cpp
 *
 *  Created on: 2020/05/24
 *      Author: iizuka
 */

#include "vm_trx/VmTransactionHandler.h"

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

	}

	this->trx = this->db->newTransaction();
}

void VmTransactionHandler::commit() {
	if(this->trx == nullptr){

	}
}

void VmTransactionHandler::rollback() {
	if(this->trx == nullptr){

	}

	doRollback();
}

void VmTransactionHandler::doRollback() {
	this->trx->rollback();
	this->trx = nullptr;
}

} /* namespace alinous */
