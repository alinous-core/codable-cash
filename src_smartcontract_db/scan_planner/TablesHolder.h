/*
 * TablesHolder.h
 *
 *  Created on: 2020/08/07
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_TABLESHOLDER_H_
#define SCAN_PLANNER_TABLESHOLDER_H_
#include "base/ArrayList.h"

namespace alinous {
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class AbstractScanTableTarget;

class TablesHolder {
public:
	TablesHolder();
	virtual ~TablesHolder();

	void addScanTarget(AbstractScanTableTarget* target) noexcept;

	void push(AbstractScanTableTarget* target) noexcept;
	AbstractScanTableTarget* pop() noexcept;
	bool isEmpty() const noexcept;

	const UnicodeString* toString() noexcept;
private:
	ArrayList<AbstractScanTableTarget> list;

	ArrayList<AbstractScanTableTarget> stack;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_TABLESHOLDER_H_ */
