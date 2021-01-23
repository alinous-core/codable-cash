/*
 * IndexResolver.h
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#ifndef SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_INDEXRESOLVER_H_
#define SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_INDEXRESOLVER_H_

#include "base/ArrayList.h"

using namespace alinous;

namespace codablecash {

class CodableDatabase;
class AbstractIndexCandidate;
class AbstractColumnsIndexWrapper;
class OrIndexCandidate;
class MultipleIndexCandidate;
class SingleColumnIndex;
class OrIndexWrapperCollection;
class MultipleColumnIndex;
class AbstractIndexCandidateCollection;

class IndexResolver {
public:
	explicit IndexResolver(CodableDatabase* db);
	virtual ~IndexResolver();

	void analyze(const AbstractIndexCandidate* candidate);

	AbstractColumnsIndexWrapper* getResult() const noexcept {
		return result;
	}

private:
	AbstractColumnsIndexWrapper* doAnalyze(const AbstractIndexCandidate* candidate);
	OrIndexWrapperCollection* analyzeOr(const OrIndexCandidate* orCandidate);
	MultipleColumnIndex* analyzeAnd(const MultipleIndexCandidate* andCandidate);

	SingleColumnIndex* handleSingleIndex(const AbstractIndexCandidate* candidate);
	AbstractColumnsIndexWrapper* handleIndexCollection(const AbstractIndexCandidateCollection* candidate);

private:
	CodableDatabase* db;
	AbstractColumnsIndexWrapper* result;

};

} /* namespace codablecash */

#endif /* SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_INDEXRESOLVER_H_ */
