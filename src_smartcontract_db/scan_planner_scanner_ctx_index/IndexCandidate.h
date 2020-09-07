/*
 * IndexCandidate.h
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_INDEX_INDEXCANDIDATE_H_
#define SCAN_PLANNER_SCANNER_CTX_INDEX_INDEXCANDIDATE_H_

#include "scan_planner_scanner_ctx_index/AbstractIndexCandidateCollection.h"

namespace codablecash {

class IndexCandidate: public AbstractIndexCandidateCollection {
public:
	IndexCandidate();
	virtual ~IndexCandidate();

	virtual AbstractIndexCandidate::IndexType getCandidateType() const noexcept;
	virtual AbstractIndexCandidate* multiply(const AbstractIndexCandidate* other) const noexcept;
	virtual AbstractIndexCandidate* copy() const noexcept;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_INDEX_INDEXCANDIDATE_H_ */
