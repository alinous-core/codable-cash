/*
 * TableIndexDetectorStack.h
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_INDEX_TABLEINDEXDETECTORSTACK_H_
#define SCAN_PLANNER_SCANNER_CTX_INDEX_TABLEINDEXDETECTORSTACK_H_

#include "base/ArrayList.h"
#include "base/RawArrayPrimitive.h"

using alinous::ArrayList;
using alinous::RawArrayPrimitive;

namespace codablecash {

class AbstractIndexCandidate;

class TableIndexDetectorStack {
public:
	TableIndexDetectorStack();
	virtual ~TableIndexDetectorStack();

	bool isEmpty() const noexcept;
	void push(AbstractIndexCandidate* candidate) noexcept;
	AbstractIndexCandidate* pop() noexcept;

	void mark() noexcept;
	void unmark() noexcept;
private:
	ArrayList<AbstractIndexCandidate> stack;
	RawArrayPrimitive<int> markStack;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_INDEX_TABLEINDEXDETECTORSTACK_H_ */
