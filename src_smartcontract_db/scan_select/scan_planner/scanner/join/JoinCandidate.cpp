/*
 * JoinCandidate.cpp
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/join/JoinCandidate.h"

#include "scan_select/scan_table/AbstractScanTableTarget.h"
#include "scan_select/scan_table/TableScanTarget.h"

#include "scan_select/scan_condition/params/ColumnIdentifierScanParam.h"

#include "scan_select/scan_planner/scanner/join/JoinOrCandidate.h"
#include "scan_select/scan_planner/scanner/join/JoinMultipleCandidate.h"

#include "schema_table/table/CdbTable.h"
#include "schema_table/table/CdbTableColumn.h"

#include "base/ArrayList.h"

#include "engine/CdbOid.h"

#include "trx/scan/transaction_scan_result/ScanResultMetadata.h"
#include "trx/scan/transaction_scan_result/ScanResultFieldMetadata.h"

#include "schema_table/record/table_record_key/CdbRecordKey.h"
#include "schema_table/record/table_record/CdbRecord.h"

#include "schema_table/record/table_record_value/AbstractCdbValue.h"

#include "schema_table/record/table_record_key/AbstractCdbKey.h"
namespace codablecash {


JoinCandidate::JoinCandidate(const JoinCandidate& inst) : AbstractJoinCandidateCollection(inst.joinType) {
	this->left = dynamic_cast<ColumnIdentifierScanParam*>(inst.left->clone());
	this->right = dynamic_cast<ColumnIdentifierScanParam*>(inst.right->clone());
}


JoinCandidate::JoinCandidate(int joinType, ColumnIdentifierScanParam* left, ColumnIdentifierScanParam* right) : AbstractJoinCandidateCollection(joinType) {
	this->left = dynamic_cast<ColumnIdentifierScanParam*>(left->clone());
	this->right = dynamic_cast<ColumnIdentifierScanParam*>(right->clone());
}

JoinCandidate::~JoinCandidate() {
	delete this->left;
	delete this->right;
}

const AbstractScanTableTarget* JoinCandidate::getLeftTarget() const noexcept {
	return this->left->getSourceTarget();
}

const AbstractScanTableTarget* JoinCandidate::getRightTarget() const noexcept {
	return this->right->getSourceTarget();
}

JoinCandidate::CandidateType JoinCandidate::getCandidateType() const noexcept {
	return JoinCandidate::CandidateType::EQUALS;
}

int JoinCandidate::getOverHeadScore(AbstractScanTableTarget* left, AbstractScanTableTarget* right) const noexcept {
	ColumnIdentifierScanParam* rightParam = getRightParam(right);

	if(rightParam->hasIndex()){
		return 1;
	}

	return 1000;
}

CdbTableIndex* JoinCandidate::getIndex(const AbstractScanTableTarget* right) const noexcept {
	CdbTableIndex* index = nullptr;

	ColumnIdentifierScanParam* rightParam = getRightParam(right);

	const AbstractScanTableTarget* target = rightParam->getSourceTarget();
	const TableScanTarget* tableTarget = dynamic_cast<const TableScanTarget*>(target);
	if(tableTarget != nullptr){
		const CdbTable* table = tableTarget->getTable();
		const CdbTableColumn* column = rightParam->getCdbColumn();
		const CdbOid* coloid = column->getOid();

		ArrayList<const CdbOid> oidlist;
		oidlist.addElement(coloid);

		index = table->findMostAvailableIndex(&oidlist);
	}

	return index;
}

const CdbTableColumn* JoinCandidate::getRightColumn(const AbstractScanTableTarget* right) const noexcept {
	const CdbTableColumn* column = nullptr;

	ColumnIdentifierScanParam* rightParam = getRightParam(right);

	const AbstractScanTableTarget* target = rightParam->getSourceTarget();
	const TableScanTarget* tableTarget = dynamic_cast<const TableScanTarget*>(target);
	if(tableTarget != nullptr){
		const CdbTable* table = tableTarget->getTable();
		column = rightParam->getCdbColumn();
	}

	return column;
}

AbstractCdbKey* JoinCandidate::makeKeyFromRecord(const CdbRecord* leftRecord) const noexcept {
	const AbstractScanTableTarget* sourceTarget = this->left->getSourceTarget();
	const ScanResultMetadata* meta = sourceTarget->getMetadata();

	const ScanResultFieldMetadata* fieldMeta = findField(meta, sourceTarget);

	CdbRecordKey* key = new CdbRecordKey();
	int pos = fieldMeta->getPosition();

	const AbstractCdbValue* v = leftRecord->get(pos);
	AbstractCdbKey* valueKey = (v != nullptr) ? v->toKey() : nullptr;

	key->addKey(valueKey);

	return key;
}

const ScanResultFieldMetadata* JoinCandidate::findField(const ScanResultMetadata* meta,
		const AbstractScanTableTarget* sourceTarget) const {
	const ArrayList<ScanResultFieldMetadata>* list = meta->getList();

	ScanResultFieldMetadata* ret = nullptr;

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		ScanResultFieldMetadata* f = list->get(i);

		if(f->match(this->left)){
			ret = f;
			break;
		}
	}

	return ret;
}

ColumnIdentifierScanParam* JoinCandidate::getRightParam(const AbstractScanTableTarget* right) const noexcept {
	if(this->left->getSourceTarget() == right){
		return this->left;
	}
	return this->right;
}


AbstractJoinCandidate* JoinCandidate::multiply(const AbstractJoinCandidate* other) const noexcept {
	JoinCandidate::CandidateType candidateType = other->getCandidateType();

	if(candidateType == JoinCandidate::CandidateType::OR){
		const JoinOrCandidate* orCandidate = dynamic_cast<const JoinOrCandidate*>(other);
		return orCandidate->multiply(this);
	}

	JoinMultipleCandidate* candidate = new JoinMultipleCandidate(this->joinType);
	candidate->mul(this);

	const AbstractJoinCandidateCollection* col = dynamic_cast<const AbstractJoinCandidateCollection*>(other);

	int maxLoop = col->size();
	for(int i = 0; i != maxLoop; ++i){
		const JoinCandidate* c = col->get(i);
		candidate->mul(c);
	}

	return candidate;
}

int JoinCandidate::size() const noexcept {
	return 1;
}

const JoinCandidate* JoinCandidate::get(int i) const noexcept {
	return this;
}

AbstractJoinCandidate* JoinCandidate::copy() const noexcept {
	return new JoinCandidate(*this);
}

} /* namespace codablecash */
