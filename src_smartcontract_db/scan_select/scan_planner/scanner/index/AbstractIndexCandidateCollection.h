/*
 * AbstractIndexCandidateCollection.h
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_INDEX_ABSTRACTINDEXCANDIDATECOLLECTION_H_
#define SCAN_PLANNER_SCANNER_CTX_INDEX_ABSTRACTINDEXCANDIDATECOLLECTION_H_

#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidate.h"

namespace codablecash {

class IndexCandidate;

class AbstractIndexCandidateCollection: public AbstractIndexCandidate {
public:
	explicit AbstractIndexCandidateCollection(IndexType indexType);
	virtual ~AbstractIndexCandidateCollection();

	virtual int size() const noexcept = 0;
	virtual const IndexCandidate* get(int i) const noexcept = 0;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_INDEX_ABSTRACTINDEXCANDIDATECOLLECTION_H_ */
