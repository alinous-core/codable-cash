/*
 * FilterConditionDitector.h
 *
 *  Created on: 2020/09/02
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_FILTERCONDITIONDITECTOR_H_
#define SCAN_PLANNER_SCANNER_CTX_FILTERCONDITIONDITECTOR_H_

#include "base/ArrayList.h"

namespace alinous {
class VirtualMachine;
}
using namespace alinous;

namespace codablecash {

class SelectScanPlanner;
class AbstractScanTableTarget;

class FilterConditionDitector {
public:
	FilterConditionDitector(VirtualMachine* vm, SelectScanPlanner* planner);
	virtual ~FilterConditionDitector();

	void detect(AbstractScanTableTarget* target);
private:
	VirtualMachine* vm;
	SelectScanPlanner* planner;
	ArrayList<AbstractScanTableTarget> list;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_FILTERCONDITIONDITECTOR_H_ */
