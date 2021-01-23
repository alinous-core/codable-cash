/*
 * ScanJoinContext.h
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCANNER_JOIN_SCANJOINCONTEXT_H_
#define TRANSACTION_SCANNER_JOIN_SCANJOINCONTEXT_H_

namespace codablecash {

class AbstractJoinCandidate;

class ScanJoinContext {
public:
	ScanJoinContext(const ScanJoinContext& inst);
	explicit ScanJoinContext(const AbstractJoinCandidate* joinCandidate);
	virtual ~ScanJoinContext();

	AbstractJoinCandidate* getJoinCandidate() const noexcept {
		return joinCandidate;
	}

private:
	AbstractJoinCandidate* joinCandidate;
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCANNER_JOIN_SCANJOINCONTEXT_H_ */
