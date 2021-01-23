/*
 * OuterJoinExecutor.cpp
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner_join/OuterJoinExecutor.h"
#include "trx/scan/transaction_scanner_join/IJoinRightSource.h"
#include "trx/scan/transaction_scanner_join/JoinCandidateCursor.h"

#include "schema_table/record/table_record/CdbRecord.h"
#include "schema_table/record/table_record_key/AbstractCdbKey.h"

#include "scan_select/scan_planner/scanner/join/AbstractJoinCandidate.h"

#include "scan_select/scan_planner/scanner/ctx/ScanJoinContext.h"

#include "base/StackRelease.h"

namespace codablecash {

OuterJoinExecutor::OuterJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right, ScanResultMetadata* metadata
		, ScanJoinContext* context, AbstractScanCondition* filterCondition)
					: AbstractJoinExecutor(left, right, metadata, context, filterCondition){
	this->leftRecord = nullptr;
	this->joinCursor = nullptr;
}

OuterJoinExecutor::~OuterJoinExecutor() {
	shutdown();

	delete this->leftRecord;
	delete this->joinCursor;
}

void OuterJoinExecutor::start() {
	AbstractJoinExecutor::start();

	AbstractJoinCandidate* joinCandidate = this->context->getJoinCandidate();
	this->joinCursor = new JoinCandidateCursor(joinCandidate);
	this->joinCursor->init();
}

bool OuterJoinExecutor::hasNext() {
	while(!this->joinCursor->finished()){
		if(!hasNextLeftRecord()){
			this->joinCursor->inc();

			delete this->leftRecord, this->leftRecord = nullptr;
			continue;
		}

		return true;
	}

	// TODO scan logic

	return false;
}

bool OuterJoinExecutor::hasNextLeftRecord() {
	if(this->leftRecord == nullptr && this->left->hasNext()){
		delete this->leftRecord, this->leftRecord = nullptr;

		const CdbRecord* rec = this->left->next();

		AbstractCdbValue* v = rec->copy();

		this->leftRecord = dynamic_cast<CdbRecord*>(rec->copy());
		onChangeLeft();
	}

	return this->leftRecord != nullptr;
}

void OuterJoinExecutor::onChangeLeft() {
	AbstractCdbKey* key = this->joinCursor->makeKey(this->leftRecord); __STP(key);

	this->right->reset(key);
}

const CdbRecord* OuterJoinExecutor::next() {
	return nullptr;
}

void OuterJoinExecutor::shutdown() {
	AbstractJoinExecutor::shutdown();
}

} /* namespace codablecash */
