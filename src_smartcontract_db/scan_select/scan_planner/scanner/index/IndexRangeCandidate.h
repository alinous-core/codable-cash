/*
 * IndexRangeCandidate.h
 *
 *  Created on: 2020/11/16
 *      Author: iizuka
 */

#ifndef SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_INDEXRANGECANDIDATE_H_
#define SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_INDEXRANGECANDIDATE_H_

#include "scan_select/scan_planner/scanner/index/IndexCandidate.h"

namespace codablecash {

class IValueProvider;

class IndexRangeCandidate : public IndexCandidate {
public:
	IndexRangeCandidate();
	virtual ~IndexRangeCandidate();

	virtual const UnicodeString* toCodeString() noexcept;

	void setBottomEq(bool bottomEq) noexcept {
		this->bottomEq = bottomEq;
	}
	bool isBottomEq() const {
		return bottomEq;
	}

	void setTopEq(bool topEq) noexcept {
		this->topEq = topEq;
	}
	bool isTopEq() const {
		return topEq;
	}

	void setTopValue(const IValueProvider* topValue) noexcept {
		this->topValue = topValue;
	}
	const IValueProvider* getTopValue() const noexcept {
		return topValue;
	}

private:
	const IValueProvider* topValue;

	bool topEq;
	bool bottomEq;
};

} /* namespace codablecash */

#endif /* SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_INDEXRANGECANDIDATE_H_ */
