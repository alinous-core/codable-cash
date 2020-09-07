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

class TableIndexDetector {
public:
	TableIndexDetector(VirtualMachine* vm, SelectScanPlanner* planner);
	virtual ~TableIndexDetector();

private:
	VirtualMachine* vm;
	SelectScanPlanner* planner;

};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_INDEX_TABLEINDEXDETECTOR_H_ */
