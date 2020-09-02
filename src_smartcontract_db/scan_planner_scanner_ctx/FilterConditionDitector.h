/*
 * FilterConditionDitector.h
 *
 *  Created on: 2020/09/02
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_FILTERCONDITIONDITECTOR_H_
#define SCAN_PLANNER_SCANNER_CTX_FILTERCONDITIONDITECTOR_H_

namespace alinous {
class VirtualMachine;
}
using namespace alinous;

namespace codablecash {

class SelectScanPlanner;

class FilterConditionDitector {
public:
	FilterConditionDitector(VirtualMachine* vm, SelectScanPlanner* planner);
	virtual ~FilterConditionDitector();

private:
	VirtualMachine* vm;
	SelectScanPlanner* planner;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_FILTERCONDITIONDITECTOR_H_ */
