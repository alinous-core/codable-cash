/*
 * JoinMuntipleCandidate.h
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_JOINMUNTIPLECANDIDATE_H_
#define SCAN_PLANNER_SCANNER_CTX_JOINMUNTIPLECANDIDATE_H_

#include "scan_planner_scanner_ctx_join/AbstractJoinCandidate.h"

namespace codablecash {

class JoinMuntipleCandidate : public AbstractJoinCandidate {
public:
	explicit JoinMuntipleCandidate(int joinType);
	virtual ~JoinMuntipleCandidate();


};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_JOINMUNTIPLECANDIDATE_H_ */
