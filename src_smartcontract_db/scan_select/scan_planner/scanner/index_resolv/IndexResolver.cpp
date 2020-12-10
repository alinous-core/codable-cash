/*
 * IndexResolver.cpp
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index_resolv/IndexResolver.h"
#include "scan_select/scan_planner/scanner/index_resolv/AbstractColumnsIndexWrapper.h"
#include "scan_select/scan_planner/scanner/index_resolv/SingleColumnIndex.h"
#include "scan_select/scan_planner/scanner/index_resolv/OrIndexWrapperCollection.h"

#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidate.h"
#include "scan_select/scan_planner/scanner/index/OrIndexCandidate.h"
#include "scan_select/scan_planner/scanner/index/MultipleIndexCandidate.h"
#include "scan_select/scan_planner/scanner/index/IndexRangeCandidate.h"

#include "engine/CodableDatabase.h"

#include "scan_select/scan_condition/params/ColumnIdentifierScanParam.h"

#include "base/StackRelease.h"

#include "scan_select/scan_planner/scanner/index_resolv/MultipleColumnIndex.h"

namespace codablecash {

IndexResolver::IndexResolver(CodableDatabase* db) {
	this->db = db;
	this->result = nullptr;
}

IndexResolver::~IndexResolver() {
	this->db = nullptr;
	delete this->result;
}

void IndexResolver::analyze(const AbstractIndexCandidate* candidate) {
	this->result = doAnalyze(candidate);
}

AbstractColumnsIndexWrapper* IndexResolver::doAnalyze(const AbstractIndexCandidate* candidate) {
	SchemaManager* schemaManager = this->db->getSchemaManager();

	AbstractIndexCandidate::IndexType candidateType = candidate->getCandidateType();

	if(candidateType == AbstractIndexCandidate::IndexType::OR){
		const OrIndexCandidate* orCandidate = dynamic_cast<const OrIndexCandidate*>(candidate);

		OrIndexWrapperCollection* orWarpper = analyzeOr(orCandidate);
		StackRelease<OrIndexWrapperCollection> stOrWrapper(orWarpper);

		if(orWarpper != nullptr && orWarpper->hasIndex(schemaManager)){
			return stOrWrapper.move();
		}
		return nullptr;
	}
	else if(candidateType == AbstractIndexCandidate::IndexType::AND){
		const MultipleIndexCandidate* andCandidate = dynamic_cast<const MultipleIndexCandidate*>(candidate);
		return analyzeAnd(andCandidate);
	}


	SingleColumnIndex* index = handleSingleIndex(candidate);
	StackRelease<SingleColumnIndex> st_index(index);

	if(index != nullptr && index->hasIndex(schemaManager)){
		return st_index.move();
	}

	return nullptr;
}

SingleColumnIndex* IndexResolver::handleSingleIndex(const AbstractIndexCandidate* candidate) {
	AbstractIndexCandidate::IndexType candidateType = candidate->getCandidateType();

	if(candidateType == AbstractIndexCandidate::IndexType::RANGE){
		const IndexRangeCandidate* rangeCandidate = dynamic_cast<const IndexRangeCandidate*>(candidate);

		const ColumnIdentifierScanParam* colp = rangeCandidate->getColumn();
		const CdbTableColumn* col = colp->getCdbColumn();

		SingleColumnIndex* index = new SingleColumnIndex();
		index->setRange(true);
		index->setTarget(colp->getTarget());
		index->setColumn(col);

		const IValueProvider* vp = rangeCandidate->getValue();
		index->setValue(vp);
		index->setBottomEq(rangeCandidate->isBottomEq());

		vp = rangeCandidate->getTopValue();
		index->setTopValue(vp);
		index->setTopEq(rangeCandidate->isTopEq());

		return index;
	}
	else if(candidateType == AbstractIndexCandidate::IndexType::RANGE_LT
			|| candidateType == AbstractIndexCandidate::IndexType::RANGE_LT_EQ){
		const IndexCandidate* indexCandidate = dynamic_cast<const IndexCandidate*>(candidate);
		const ColumnIdentifierScanParam* colp = indexCandidate->getColumn();
		const CdbTableColumn* col = colp->getCdbColumn();
		const IValueProvider* vp = indexCandidate->getValue();

		SingleColumnIndex* index = new SingleColumnIndex();
		index->setRange(true);

		index->setTarget(colp->getTarget());
		index->setColumn(col);

		index->setTopValue(vp);
		index->setTopEq(indexCandidate->hasEq());

		return index;
	}
	else if(candidateType == AbstractIndexCandidate::IndexType::RANGE_GT
			|| candidateType == AbstractIndexCandidate::IndexType::RANGE_GT_EQ){
		const IndexCandidate* indexCandidate = dynamic_cast<const IndexCandidate*>(candidate);
		const ColumnIdentifierScanParam* colp = indexCandidate->getColumn();
		const CdbTableColumn* col = colp->getCdbColumn();
		const IValueProvider* vp = indexCandidate->getValue();

		SingleColumnIndex* index = new SingleColumnIndex();
		index->setRange(true);

		index->setTarget(colp->getTarget());
		index->setColumn(col);

		index->setValue(vp);
		index->setBottomEq(indexCandidate->hasEq());

		return index;
	}

	const IndexCandidate* indexCandidate = dynamic_cast<const IndexCandidate*>(candidate);
	const ColumnIdentifierScanParam* colp = indexCandidate->getColumn();
	const CdbTableColumn* col = colp->getCdbColumn();
	const IValueProvider* vp = indexCandidate->getValue();

	SingleColumnIndex* index = new SingleColumnIndex();

	index->setTarget(colp->getTarget());
	index->setColumn(col);
	index->setValue(vp);

	return index;
}

OrIndexWrapperCollection* IndexResolver::analyzeOr(const OrIndexCandidate* orCandidate) {
	OrIndexWrapperCollection* wrapper = new OrIndexWrapperCollection();

	AbstractIndexCandidateCollection* c = orCandidate->get(0);
	const IndexCandidate* ic = c->get(0);
	const ColumnIdentifierScanParam* colp = ic->getColumn();

	wrapper->setTarget(colp->getTarget());

	int maxLoop = orCandidate->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractIndexCandidateCollection* candidate = orCandidate->get(i);

		AbstractColumnsIndexWrapper* w = handleIndexCollection(candidate);
		wrapper->add(w);
	}

	return wrapper;
}

AbstractColumnsIndexWrapper* IndexResolver::handleIndexCollection(const AbstractIndexCandidateCollection* candidate) {
	AbstractIndexCandidate::IndexType candidateType = candidate->getCandidateType();

	if(candidateType == AbstractIndexCandidate::IndexType::AND){
		const MultipleIndexCandidate* andCandidate = dynamic_cast<const MultipleIndexCandidate*>(candidate);
		return analyzeAnd(andCandidate);
	}

	return handleSingleIndex(candidate);
}


MultipleColumnIndex* IndexResolver::analyzeAnd(const MultipleIndexCandidate* andCandidate) {
	MultipleColumnIndex* wrapper = new MultipleColumnIndex();

	const IndexCandidate* c = andCandidate->get(0);
	const IndexCandidate* ic = c->get(0);
	const ColumnIdentifierScanParam* colp = ic->getColumn();

	wrapper->setTarget(colp->getTarget());

	int maxLoop = andCandidate->size();
	for(int i = 0; i != maxLoop; ++i){
		const IndexCandidate* candidate = andCandidate->get(i);

		SingleColumnIndex* singleIndex = handleSingleIndex(candidate);
		wrapper->add(singleIndex);
	}

	return wrapper;
}

} /* namespace codablecash */
