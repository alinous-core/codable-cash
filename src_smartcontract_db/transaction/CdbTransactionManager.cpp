/*
 * CdbTransactionManager.cpp
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#include "transaction/CdbTransactionManager.h"
#include "transaction/CdbTransaction.h"
#include "transaction/SchemaObjectIdPublisher.h"

#include "engine/CodableDatabase.h"


namespace codablecash {

CdbTransactionManager::CdbTransactionManager(CodableDatabase* db) {
	this->db = db;
	this->schemaIdPublisher = nullptr;
}

CdbTransactionManager::~CdbTransactionManager() {
	this->db = nullptr;
	delete this->schemaIdPublisher;
}

void CdbTransactionManager::schemaLoaded(Schema* sc) {
	delete this->schemaIdPublisher;
	this->schemaIdPublisher = new SchemaObjectIdPublisher(sc);
}

CdbTransaction* CdbTransactionManager::newTransaction(uint64_t transactionId) {

	CdbTransaction* trx = new CdbTransaction(this, transactionId);

	return trx;
}

SchemaObjectIdPublisher* CdbTransactionManager::getSchemaObjectIdPublisher() const noexcept {
	return this->schemaIdPublisher;
}

} /* namespace codablecash */
