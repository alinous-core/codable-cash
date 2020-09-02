/*
 * JoinCandidate.h
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_JOINCANDIDATE_H_
#define SCAN_PLANNER_SCANNER_CTX_JOINCANDIDATE_H_

#include "scan_planner_scanner_ctx_join/AbstractJoinCandidate.h"

namespace codablecash {

class AbstractJoinScanTarget;

class JoinCandidate : public AbstractJoinCandidate {
public:
	explicit JoinCandidate(int joinType);
	virtual ~JoinCandidate();

};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_JOINCANDIDATE_H_ */
