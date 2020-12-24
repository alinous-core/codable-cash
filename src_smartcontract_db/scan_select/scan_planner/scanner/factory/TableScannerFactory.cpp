/*
 * TableScannerFactory.cpp
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/factory/TableScannerFactory.h"

#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidate.h"

#include "scan_select/scan_planner/scanner/index_resolv/AbstractColumnsIndexWrapper.h"
#include "scan_select/scan_planner/scanner/index_resolv/OrIndexWrapperCollection.h"

#include "vm/VirtualMachine.h"
#include "vm/vm_trx/VmTransactionHandler.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbOid.h"

#include "schema_table/table/CdbTable.h"

#include "schema_table/table_store/CdbStorageManager.h"

#include "trx/transaction/CdbTransaction.h"

#include "trx/scan/transaction_scanner/TableTransactionScanner.h"
#include "trx/scan/transaction_scanner/TableTransactionOrIndexScanner.h"

#include "scan_select/scan_planner/scanner/join/AbstractJoinCandidate.h"
#include "scan_select/scan_planner/scanner/join/JoinOrCandidate.h"

#include "trx/scan/transaction_scanner_join_right/RightTableIndexTransactionScanner.h"
#include "trx/scan/transaction_scanner_join_right/RightTableOrTransactionScanner.h"
#include "trx/scan/transaction_scanner_join_right/RightTableBufferedTransactionScanner.h"

#include "scan_select/scan_planner/scanner/ctx/ScanJoinContext.h"

#include "scan_select/scan_condition/base/AbstractScanCondition.h"

namespace codablecash {

TableScannerFactory::TableScannerFactory(AbstractScanTableTarget* target, const CdbTable* table,
		const ScanResultMetadata* metadata, AbstractColumnsIndexWrapper* indexCandidate)
				: AbstractScannerFactory(metadata){
	this->target = target;
	this->indexCandidate = indexCandidate;
	this->table = table;
}

TableScannerFactory::~TableScannerFactory() {
	delete this->indexCandidate;

	this->target = nullptr;
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
		scanner = new TableTransactionScanner(this->metadata, trx, tableStore, this->filterCondition);
	}
	else{
		scanner = createIndexScannerAsLeftSource(vm, planner, tableStore, trx);
	}

	return scanner;
}

IJoinLeftSource* TableScannerFactory::createIndexScannerAsLeftSource(VirtualMachine* vm, SelectScanPlanner* planner,
		TableStore* tableStore, CdbTransaction* trx) {
	IJoinLeftSource* scanner = nullptr;

	if(this->indexCandidate->isOr()){
		OrIndexWrapperCollection* orIndex = dynamic_cast<OrIndexWrapperCollection*>(this->indexCandidate);
		scanner = new TableTransactionOrIndexScanner(this->metadata, trx, tableStore, this->filterCondition, orIndex);
	}
	else if(this->indexCandidate->isRange()){
		// TODO rangeScan
	}
	else{
		// TODO normal index
	}

	return scanner;
}

IJoinRightSource* TableScannerFactory::createScannerAsRightSource(
		VirtualMachine* vm, SelectScanPlanner* planner, const ScanJoinContext* joinContext) {
	IJoinRightSource* rightSource = nullptr;

	AbstractJoinCandidate* joinCandidate = joinContext->getJoinCandidate();
	if(joinCandidate != nullptr){
		rightSource = createIndexScannerAsRightSource(vm, planner, joinCandidate);
	}
	else{
		// cross join
	}

	// TODO right source

	return rightSource;
}

IJoinRightSource* TableScannerFactory::createIndexScannerAsRightSource(
		VirtualMachine* vm, SelectScanPlanner* planner,
		AbstractJoinCandidate* joinCandidate) {
	IJoinRightSource* rightSource = nullptr;

	VmTransactionHandler* trxHandler = vm->getTransactionHandler();
	CdbTransaction* trx = trxHandler->getTransaction();

	AbstractJoinCandidate::CandidateType type = joinCandidate->getCandidateType();
	if(type == AbstractJoinCandidate::CandidateType::OR){
		JoinOrCandidate* orCandidate = dynamic_cast<JoinOrCandidate*>(joinCandidate);
		rightSource = new RightTableOrTransactionScanner(this->metadata, trx, this->table, this->filterCondition, orCandidate);

	}else{
		CdbTableIndex* index = joinCandidate->getIndex(this->target);

		if(index != nullptr){
			rightSource = new RightTableIndexTransactionScanner(this->metadata, trx, this->table, this->filterCondition, index);
		}
		else{
			rightSource = new RightTableBufferedTransactionScanner(this->metadata, trx, this->table, this->filterCondition, joinCandidate);
		}
	}

	return rightSource;
}

} /* namespace codablecash */
