/*
 * JoinCandidateCursor.h
 *
 *  Created on: 2021/01/23
 *      Author: iizuka
 */

#ifndef TRX_SCAN_TRANSACTION_SCANNER_JOIN_JOINCANDIDATECURSOR_H_
#define TRX_SCAN_TRANSACTION_SCANNER_JOIN_JOINCANDIDATECURSOR_H_

#include "base/ArrayList.h"

using alinous::ArrayList;

namespace codablecash {

class AbstractJoinCandidate;
class AbstractJoinCandidateCollection;

class JoinCandidateCursor {
public:
	explicit JoinCandidateCursor(AbstractJoinCandidate* joinCandidate);
	virtual ~JoinCandidateCursor();

	void init() noexcept;
private:
	AbstractJoinCandidate* joinCandidate;
	ArrayList<const AbstractJoinCandidateCollection> list;
};

} /* namespace codablecash */

#endif /* TRX_SCAN_TRANSACTION_SCANNER_JOIN_JOINCANDIDATECURSOR_H_ */
