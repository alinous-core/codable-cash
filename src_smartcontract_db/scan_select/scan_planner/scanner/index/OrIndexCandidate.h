/*
 * OrIndexCandidate.h
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_INDEX_ORINDEXCANDIDATE_H_
#define SCAN_PLANNER_SCANNER_CTX_INDEX_ORINDEXCANDIDATE_H_

#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidate.h"

#include "base/ArrayList.h"

using alinous::ArrayList;

namespace codablecash {

class AbstractIndexCandidateCollection;

class OrIndexCandidate : public AbstractIndexCandidate {
public:
	OrIndexCandidate(const OrIndexCandidate& inst);
	OrIndexCandidate();
	virtual ~OrIndexCandidate();

	virtual AbstractIndexCandidate::IndexType getCandidateType() const noexcept;
	virtual AbstractIndexCandidate* multiply(const AbstractIndexCandidate* other) const noexcept;
	virtual AbstractIndexCandidate* copy() const noexcept;

	void add(const AbstractIndexCandidateCollection* candidate) noexcept;

	virtual const UnicodeString* toCodeString() noexcept;

	int size() const noexcept;
	AbstractIndexCandidateCollection* get(int i) const noexcept;

private:
	AbstractIndexCandidate* multiplyOr(const OrIndexCandidate* other) const noexcept;
	void multiply(const OrIndexCandidate* other, const AbstractIndexCandidateCollection* col, OrIndexCandidate* newCond) const noexcept;

private:
	ArrayList<AbstractIndexCandidateCollection> list;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_INDEX_ORINDEXCANDIDATE_H_ */
