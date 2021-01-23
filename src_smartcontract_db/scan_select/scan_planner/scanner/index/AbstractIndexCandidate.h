/*
 * AbstractIndexCandidate.h
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_INDEX_ABSTRACTINDEXCANDIDATE_H_
#define SCAN_PLANNER_SCANNER_CTX_INDEX_ABSTRACTINDEXCANDIDATE_H_

namespace alinous {
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class AbstractIndexCandidate {
public:
	typedef enum __IndexType{
		EQUALS,
		RANGE,
		RANGE_GT,
		RANGE_GT_EQ,
		RANGE_LT,
		RANGE_LT_EQ,
		AND,
		OR
	} IndexType;

	explicit AbstractIndexCandidate(IndexType indexType);
	virtual ~AbstractIndexCandidate();

	virtual AbstractIndexCandidate::IndexType getCandidateType() const noexcept = 0;
	virtual AbstractIndexCandidate* multiply(const AbstractIndexCandidate* other) const noexcept = 0;
	virtual AbstractIndexCandidate* copy() const noexcept = 0;
	virtual const UnicodeString* toCodeString() noexcept = 0;

protected:
	void resetStr() noexcept;

protected:
	IndexType indexType;
	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_INDEX_ABSTRACTINDEXCANDIDATE_H_ */
