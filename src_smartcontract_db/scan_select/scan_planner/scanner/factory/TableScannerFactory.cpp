/*
 * TableScannerFactory.cpp
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/factory/TableScannerFactory.h"

#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidate.h"

#include "scan_select/scan_planner/scanner/index_resolv/AbstractColumnsIndexWrapper.h"

#include "trx/scan/transaction_scanner/TableTransactionScanner.h"

#include "vm/VirtualMachine.h"

#include "vm/vm_trx/VmTransactionHandler.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbOid.h"

#include "schema_table/table/CdbTable.h"

#include "schema_table/table_store/CdbStorageManager.h"

#include "trx/transaction/CdbTransaction.h"
namespace codablecash {

TableScannerFactory::TableScannerFactory(const CdbTable* table, const ScanResultMetadata* metadata, AbstractColumnsIndexWrapper* indexCandidate)
				: AbstractScannerFactory(metadata){
	this->indexCandidate = indexCandidate;
	this->table = table;
}

TableScannerFactory::~TableScannerFactory() {
	delete this->indexCandidate;

	this->table = nullptr;
}

IJoinLeftSource* TableScannerFactory::createScannerAsLeftSource(
		VirtualMachine* vm, SelectScanPlanner* planner) {
	CodableDatabase* db = vm->getDb();
	CdbStorageManager* storageManager = db->getStorageManager();

	VmTransactionHandler* trxHandler = vm->getTransactionHandler();
	CdbTransaction* trx = trxHandler->getTransaction();

	const CdbOid* tableoid = this->table->getOid();
	TableStore* tableStore = storageManager->getTableStore(tableoid);

	IJoinLeftSource* scanner = nullptr;

	if(this->indexCandidate == nullptr){
		scanner = new TableTransactionScanner(trx, tableStore);
	}
	// TODO left source

	return scanner;
}

IJoinRightSource* TableScannerFactory::createScannerAsRightSource(
		VirtualMachine* vm, SelectScanPlanner* planner, const ScanJoinContext* joinContext) {
	// TODO right source

	return nullptr;
}

} /* namespace codablecash */
