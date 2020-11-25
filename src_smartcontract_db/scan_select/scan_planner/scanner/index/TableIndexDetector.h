/*
 * TableIndexDetector.h
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_INDEX_TABLEINDEXDETECTOR_H_
#define SCAN_PLANNER_SCANNER_CTX_INDEX_TABLEINDEXDETECTOR_H_

namespace alinous {
class VirtualMachine;
}
using namespace alinous;

namespace codablecash {

class SelectScanPlanner;
class AbstractScanCondition;
class TableIndexDetectorStack;
class AbstractIndexCandidate;
class TableScanTarget;
class ColumnIdentifierScanParam;
class IValueProvider;

class TableIndexDetector {
public:
	TableIndexDetector(VirtualMachine* vm, SelectScanPlanner* planner, TableScanTarget* tableScanTarget);
	virtual ~TableIndexDetector();

	void detect(AbstractScanCondition* cond);

	void push(AbstractIndexCandidate* candidate) noexcept;
	AbstractIndexCandidate* pop() noexcept;

	bool isEmpty() const noexcept;

	TableIndexDetectorStack* getStack() const noexcept {
		return stack;
	}

private:
	VirtualMachine* vm;
	SelectScanPlanner* planner;
	TableScanTarget* tableScanTarget;

	TableIndexDetectorStack* stack;

};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_INDEX_TABLEINDEXDETECTOR_H_ */
