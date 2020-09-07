/*
 * AbstractIndexCandidateCollection.h
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_INDEX_ABSTRACTINDEXCANDIDATECOLLECTION_H_
#define SCAN_PLANNER_SCANNER_CTX_INDEX_ABSTRACTINDEXCANDIDATECOLLECTION_H_

#include "scan_planner_scanner_ctx_index/AbstractIndexCandidate.h"

namespace codablecash {

class AbstractIndexCandidateCollection: public AbstractIndexCandidate {
public:
	AbstractIndexCandidateCollection();
	virtual ~AbstractIndexCandidateCollection();
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_INDEX_ABSTRACTINDEXCANDIDATECOLLECTION_H_ */
