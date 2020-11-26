/*
 * IndexResolver.cpp
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index_resolv/IndexResolver.h"

#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidate.h"
#include "scan_select/scan_planner/scanner/index/OrIndexCandidate.h"
#include "scan_select/scan_planner/scanner/index/MultipleIndexCandidate.h"

namespace codablecash {

IndexResolver::IndexResolver(CodableDatabase* db) {
	this->db = db;
}

IndexResolver::~IndexResolver() {
	this->db = nullptr;
}

void IndexResolver::analyze(const AbstractIndexCandidate* candidate) {
	AbstractIndexCandidate::IndexType candidateType = candidate->getCandidateType();

	if(candidateType == AbstractIndexCandidate::IndexType::OR){
		const OrIndexCandidate* orCandidate = dynamic_cast<const OrIndexCandidate*>(candidate);
		analyzeOr(orCandidate);
		return;
	}
	else if(candidateType == AbstractIndexCandidate::IndexType::OR){
		const MultipleIndexCandidate* andCandidate = dynamic_cast<const MultipleIndexCandidate*>(candidate);
		analyzeAnd(andCandidate);
		return;
	}
}

void IndexResolver::analyzeOr(const OrIndexCandidate* orCandidate) {

}

void IndexResolver::analyzeAnd(const MultipleIndexCandidate* andCandidate) {
}

} /* namespace codablecash */
