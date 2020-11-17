/*
 * IndexCandidate.cpp
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index/IndexCandidate.h"
#include "scan_select/scan_planner/scanner/index/OrIndexCandidate.h"
#include "scan_select/scan_planner/scanner/index/MultipleIndexCandidate.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"

#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidateCollection.h"

#include "scan_select/scan_condition/params/ColumnIdentifierScanParam.h"

#include "scan_select/scan_condition/base/IValueProvider.h"

#include "schema_table/table/CdbTableColumn.h"


using namespace alinous;

namespace codablecash {

IndexCandidate::IndexCandidate(const IndexCandidate& inst) : AbstractIndexCandidateCollection(inst) {
	this->column = inst.column;
	this->value = inst.value;
}

IndexCandidate::IndexCandidate(IndexType indexType) : AbstractIndexCandidateCollection(indexType) {
	this->column = nullptr;
	this->value = nullptr;
}

IndexCandidate::~IndexCandidate() {

}

AbstractIndexCandidate::IndexType IndexCandidate::getCandidateType() const noexcept {
	return this->indexType;
}

AbstractIndexCandidate* IndexCandidate::multiply(const AbstractIndexCandidate* other) const noexcept {
	AbstractIndexCandidate::IndexType candidateType = other->getCandidateType();

	if(candidateType == AbstractIndexCandidate::IndexType::OR){
		const OrIndexCandidate* orCandidate = dynamic_cast<const OrIndexCandidate*>(other);
		return orCandidate->multiply(this);
	}

	MultipleIndexCandidate* candidate = new MultipleIndexCandidate();

	AbstractIndexCandidateCollection* col = dynamic_cast<AbstractIndexCandidateCollection*>(other->copy());
	__STP(col);

	int maxLoop = col->size();
	for(int i = 0; i != maxLoop; ++i){
		const IndexCandidate* c = col->get(i);
		candidate->mul(c);
	}

	return candidate;
}

bool IndexCandidate::isRange() const noexcept {
	return this->indexType == AbstractIndexCandidate::IndexType::RANGE_GT
			|| this->indexType == AbstractIndexCandidate::IndexType::RANGE_GT_EQ
			|| this->indexType == AbstractIndexCandidate::IndexType::RANGE_LT
			|| this->indexType == AbstractIndexCandidate::IndexType::RANGE_LT_EQ;
}


AbstractIndexCandidate* IndexCandidate::copy() const noexcept {
	return new IndexCandidate(*this);
}

int IndexCandidate::size() const noexcept {
	return 1;
}

const IndexCandidate* IndexCandidate::get(int i) const noexcept {
	return this;
}

bool IndexCandidate::isSameColumn(const IndexCandidate* other) {
	const CdbTableColumn* cdbColumn = this->column->getCdbColumn();
	const CdbTableColumn* cdbColumn2 = other->column->getCdbColumn();

	const UnicodeString* name = cdbColumn->getName();
	const UnicodeString* name2 = cdbColumn2->getName();

	return name->equals(name2);
}


} /* namespace codablecash */
