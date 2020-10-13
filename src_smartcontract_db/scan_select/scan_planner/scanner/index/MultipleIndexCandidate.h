/*
 * MultipleIndexCandidate.h
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_INDEX_MULTIPLEINDEXCANDIDATE_H_
#define SCAN_PLANNER_SCANNER_CTX_INDEX_MULTIPLEINDEXCANDIDATE_H_

#include "scan_select/scan_planner_scanner_ctx_index/AbstractIndexCandidateCollection.h"

#include "base/ArrayList.h"

using alinous::ArrayList;

namespace codablecash {

class MultipleIndexCandidate: public AbstractIndexCandidateCollection {
public:
	MultipleIndexCandidate(const MultipleIndexCandidate& inst);
	MultipleIndexCandidate();
	virtual ~MultipleIndexCandidate();

	virtual AbstractIndexCandidate::IndexType getCandidateType() const noexcept;
	virtual AbstractIndexCandidate* multiply(const AbstractIndexCandidate* other) const noexcept;
	virtual AbstractIndexCandidate* copy() const noexcept;

	virtual int size() const noexcept;
	virtual const IndexCandidate* get(int i) const noexcept;

	void mul(const IndexCandidate* candidate) noexcept;

private:
	ArrayList<IndexCandidate> list;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_INDEX_MULTIPLEINDEXCANDIDATE_H_ */
