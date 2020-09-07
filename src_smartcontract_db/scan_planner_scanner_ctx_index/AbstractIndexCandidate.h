/*
 * AbstractIndexCandidate.h
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_INDEX_ABSTRACTINDEXCANDIDATE_H_
#define SCAN_PLANNER_SCANNER_CTX_INDEX_ABSTRACTINDEXCANDIDATE_H_

namespace codablecash {

class AbstractIndexCandidate {
public:
	enum IndexType{
		EQUALS,
		AND,
		OR
	};

	AbstractIndexCandidate();
	virtual ~AbstractIndexCandidate();

	virtual AbstractIndexCandidate::IndexType getCandidateType() const noexcept = 0;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_INDEX_ABSTRACTINDEXCANDIDATE_H_ */
