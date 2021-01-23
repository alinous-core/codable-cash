/*
 * OuterJoinExecutor.cpp
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner_join/OuterJoinExecutor.h"

#include "schema_table/record/table_record/CdbRecord.h"

#include "trx/scan/transaction_scanner_join/IJoinRightSource.h"

namespace codablecash {

OuterJoinExecutor::OuterJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right, ScanResultMetadata* metadata
		, ScanJoinContext* context, AbstractScanCondition* filterCondition)
					: AbstractJoinExecutor(left, right, metadata, context, filterCondition){
	this->leftRecord = nullptr;
}

OuterJoinExecutor::~OuterJoinExecutor() {
	shutdown();
}

void OuterJoinExecutor::start() {
	AbstractJoinExecutor::start();
}

bool OuterJoinExecutor::hasNext() {
	if(!hasNextLeftRecord()){
		return false;
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
	//this->right->reset()
}

const CdbRecord* OuterJoinExecutor::next() {
	return nullptr;
}

void OuterJoinExecutor::shutdown() {
	AbstractJoinExecutor::shutdown();
}

} /* namespace codablecash */
