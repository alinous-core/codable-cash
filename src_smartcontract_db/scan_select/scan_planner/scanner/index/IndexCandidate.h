/*
 * IndexCandidate.h
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_INDEX_INDEXCANDIDATE_H_
#define SCAN_PLANNER_SCANNER_CTX_INDEX_INDEXCANDIDATE_H_

#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidateCollection.h"

namespace codablecash {

class ColumnIdentifierScanParam;
class IValueProvider;

class IndexCandidate: public AbstractIndexCandidateCollection {
public:
	IndexCandidate(const IndexCandidate& inst);
	IndexCandidate();
	virtual ~IndexCandidate();

	virtual AbstractIndexCandidate::IndexType getCandidateType() const noexcept;
	virtual AbstractIndexCandidate* multiply(const AbstractIndexCandidate* other) const noexcept;
	virtual AbstractIndexCandidate* copy() const noexcept;

	virtual int size() const noexcept;
	virtual const IndexCandidate* get(int i) const noexcept;

private:
	const ColumnIdentifierScanParam* column;
	const IValueProvider* value;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_INDEX_INDEXCANDIDATE_H_ */
