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
class CdbRecord;
class AbstractCdbKey;

class JoinCandidateCursor {
public:
	explicit JoinCandidateCursor(AbstractJoinCandidate* joinCandidate);
	virtual ~JoinCandidateCursor();

	void init() noexcept;
	bool finished() const noexcept;
	void inc() noexcept;

	AbstractCdbKey* makeKey(const CdbRecord* leftRecord) noexcept;

private:
	AbstractJoinCandidate* joinCandidate;
	ArrayList<const AbstractJoinCandidateCollection> list;

	int pos;
};

} /* namespace codablecash */

#endif /* TRX_SCAN_TRANSACTION_SCANNER_JOIN_JOINCANDIDATECURSOR_H_ */
