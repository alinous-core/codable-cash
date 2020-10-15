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
class VirtualMachine;
}
using namespace alinous;

namespace codablecash {

class AbstractScanTableTarget;
class SelectScanPlanner;
class AbstractScannerFactory;

class TablesHolder {
public:
	TablesHolder();
	virtual ~TablesHolder();

	void addScanTarget(AbstractScanTableTarget* target) noexcept;

	void push(AbstractScanTableTarget* target) noexcept;
	AbstractScanTableTarget* pop() noexcept;
	bool isEmpty() const noexcept;

	const UnicodeString* toString() noexcept;

	void resolveTable(VirtualMachine* vm, SelectScanPlanner* planner);
	void buildScannerFactories(VirtualMachine* vm, SelectScanPlanner* planner);

private:
	AbstractScannerFactory* buildScanFactory(VirtualMachine* vm, SelectScanPlanner* planner);
	AbstractScanTableTarget* buildOuterJoinTarget();

private:
	ArrayList<AbstractScanTableTarget> list;

	ArrayList<AbstractScanTableTarget> stack;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_TABLESHOLDER_H_ */
