/*
 * AbstractJoinCandidateCollection.h
 *
 *  Created on: 2020/09/03
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_JOIN_ABSTRACTJOINCANDIDATECOLLECTION_H_
#define SCAN_PLANNER_SCANNER_CTX_JOIN_ABSTRACTJOINCANDIDATECOLLECTION_H_

#include "scan_planner_scanner_ctx_join/AbstractJoinCandidate.h"

namespace codablecash {

class AbstractJoinCandidateCollection : public AbstractJoinCandidate {
public:
	AbstractJoinCandidateCollection(int joinType);
	virtual ~AbstractJoinCandidateCollection();
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_JOIN_ABSTRACTJOINCANDIDATECOLLECTION_H_ */
