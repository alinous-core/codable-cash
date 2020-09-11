/*
 * FilterConditionStack.h
 *
 *  Created on: 2020/09/06
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_FILTERCONDITIONSTACK_H_
#define SCAN_PLANNER_SCANNER_CTX_FILTERCONDITIONSTACK_H_

#include "base/ArrayList.h"
#include "base/RawArrayPrimitive.h"

using alinous::ArrayList;
using alinous::RawArrayPrimitive;

namespace codablecash {

class AbstractScanCondition;

class FilterConditionStack {
public:
	FilterConditionStack();
	virtual ~FilterConditionStack();

	bool isEmpty() const noexcept;
	void push(AbstractScanCondition* cond) noexcept;
	AbstractScanCondition* pop() noexcept;

	void mark() noexcept;
	void unmark() noexcept;

private:
	ArrayList<AbstractScanCondition> stack;
	RawArrayPrimitive<int> markStack;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_FILTERCONDITIONSTACK_H_ */
