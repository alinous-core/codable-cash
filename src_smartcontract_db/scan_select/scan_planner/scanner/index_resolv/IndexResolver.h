/*
 * IndexResolver.h
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#ifndef SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_INDEXRESOLVER_H_
#define SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_INDEXRESOLVER_H_

namespace codablecash {

class CodableDatabase;
class AbstractIndexCandidate;
class OrIndexCandidate;
class MultipleIndexCandidate;

class IndexResolver {
public:
	explicit IndexResolver(CodableDatabase* db);
	virtual ~IndexResolver();

	void analyze(const AbstractIndexCandidate* candidate);

private:
	void analyzeOr(const OrIndexCandidate* orCandidate);
	void analyzeAnd(const MultipleIndexCandidate* andCandidate);

private:
	CodableDatabase* db;
};

} /* namespace codablecash */

#endif /* SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_INDEXRESOLVER_H_ */
