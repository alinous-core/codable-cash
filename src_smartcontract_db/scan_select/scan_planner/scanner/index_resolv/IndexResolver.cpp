/*
 * IndexResolver.cpp
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index_resolv/IndexResolver.h"
#include "scan_select/scan_planner/scanner/index_resolv/AbstractColumnsIndexWrapper.h"

#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidate.h"
#include "scan_select/scan_planner/scanner/index/OrIndexCandidate.h"
#include "scan_select/scan_planner/scanner/index/MultipleIndexCandidate.h"
#include "scan_select/scan_planner/scanner/index/IndexRangeCandidate.h"

#include "engine/CodableDatabase.h"

#include "scan_select/scan_condition/params/ColumnIdentifierScanParam.h"

#include "scan_select/scan_planner/scanner/index_resolv/SingleColumnIndex.h"
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
	ArrayList<AbstractColumnsIndexWrapper> list;

}

void IndexResolver::doAnalyze(const AbstractIndexCandidate* candidate, ArrayList<AbstractColumnsIndexWrapper>* list) {
	AbstractIndexCandidate::IndexType candidateType = candidate->getCandidateType();

	if(candidateType == AbstractIndexCandidate::IndexType::OR){
		const OrIndexCandidate* orCandidate = dynamic_cast<const OrIndexCandidate*>(candidate);
		analyzeOr(orCandidate, list);
		return;
	}
	else if(candidateType == AbstractIndexCandidate::IndexType::AND){
		const MultipleIndexCandidate* andCandidate = dynamic_cast<const MultipleIndexCandidate*>(candidate);
		analyzeAnd(andCandidate, list);
		return;
	}

	SchemaManager* schemaManager = this->db->getSchemaManager();

	if(candidateType == AbstractIndexCandidate::IndexType::RANGE){
		const IndexRangeCandidate* rangeCandidate = dynamic_cast<const IndexRangeCandidate*>(candidate);

		const ColumnIdentifierScanParam* colp = rangeCandidate->getColumn();
		const CdbTableColumn* col = colp->getCdbColumn();

		SingleColumnIndex* index = new SingleColumnIndex();
		index->setRange(true);
		list->addElement(index);

		const IValueProvider* vp = rangeCandidate->getValue();
		index->setValue(vp);
		index->setBottomEq(rangeCandidate->isBottomEq());

		vp = rangeCandidate->getTopValue();
		index->setTopValue(vp);
		index->setTopEq(rangeCandidate->isTopEq());

		return;
	}

	const IndexCandidate* indexCandidate = dynamic_cast<const IndexCandidate*>(candidate);
	const ColumnIdentifierScanParam* colp = indexCandidate->getColumn();
	const CdbTableColumn* col = colp->getCdbColumn();
	const IValueProvider* vp = indexCandidate->getValue();

	SingleColumnIndex* index = new SingleColumnIndex();
	list->addElement(index);

	index->setColumn(col);
	index->setValue(vp);
}

void IndexResolver::analyzeOr(const OrIndexCandidate* orCandidate, ArrayList<AbstractColumnsIndexWrapper>* list) {


}

void IndexResolver::analyzeAnd(const MultipleIndexCandidate* andCandidate, ArrayList<AbstractColumnsIndexWrapper>* list) {
	int maxLoop = andCandidate->size();
	for(int i = 0; i != maxLoop; ++i){
		const IndexCandidate* candidate = andCandidate->get(i);
	}
}

} /* namespace codablecash */
