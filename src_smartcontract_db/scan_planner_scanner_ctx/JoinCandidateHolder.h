/*
 * JoinCandidateHolder.h
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_JOINCANDIDATEHOLDER_H_
#define SCAN_PLANNER_SCANNER_CTX_JOINCANDIDATEHOLDER_H_

#include "base/ArrayList.h"

using alinous::ArrayList;

namespace codablecash {

class AbstractJoinCandidate;

class JoinCandidateHolder {
public:
	JoinCandidateHolder();
	virtual ~JoinCandidateHolder();

private:
	ArrayList<AbstractJoinCandidate> stack;

};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_JOINCANDIDATEHOLDER_H_ */
