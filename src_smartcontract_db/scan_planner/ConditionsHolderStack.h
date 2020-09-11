/*
 * ConditionsHolderStack.h
 *
 *  Created on: 2020/09/06
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_CONDITIONSHOLDERSTACK_H_
#define SCAN_PLANNER_CONDITIONSHOLDERSTACK_H_

#include "base/ArrayList.h"
#include "base/RawArrayPrimitive.h"

using alinous::ArrayList;
using alinous::RawArrayPrimitive;

namespace codablecash {

class AbstractScanConditionElement;

class ConditionsHolderStack {
public:
	ConditionsHolderStack();
	virtual ~ConditionsHolderStack();

	bool isEmpty() const noexcept;
	void push(AbstractScanConditionElement* candidate) noexcept;
	AbstractScanConditionElement* pop() noexcept;

	int size() const noexcept;
	AbstractScanConditionElement* get(int index) const noexcept;

	void mark() noexcept;
	void unmark() noexcept;

private:
	ArrayList<AbstractScanConditionElement> stack;
	RawArrayPrimitive<int> markStack;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_CONDITIONSHOLDERSTACK_H_ */
