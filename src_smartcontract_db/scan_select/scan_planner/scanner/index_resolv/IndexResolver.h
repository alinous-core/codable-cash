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

class IndexResolver {
public:
	explicit IndexResolver(CodableDatabase* db);
	virtual ~IndexResolver();

	void analyze(const AbstractIndexCandidate* candidate);

private:
	void doAnalyze(const AbstractIndexCandidate* candidate, ArrayList<AbstractColumnsIndexWrapper>* list);
	void analyzeOr(const OrIndexCandidate* orCandidate, ArrayList<AbstractColumnsIndexWrapper>* list);
	void analyzeAnd(const MultipleIndexCandidate* andCandidate, ArrayList<AbstractColumnsIndexWrapper>* list);

	SingleColumnIndex* handleIndex(const AbstractIndexCandidate* candidate);

private:
	CodableDatabase* db;
	AbstractColumnsIndexWrapper* result;

};

} /* namespace codablecash */

#endif /* SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_INDEXRESOLVER_H_ */
