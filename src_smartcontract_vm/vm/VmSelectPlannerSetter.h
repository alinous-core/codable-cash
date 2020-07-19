/*
 * VmSelectPlannerSetter.h
 *
 *  Created on: 2020/07/19
 *      Author: iizuka
 */

#ifndef VM_VMSELECTPLANNERSETTER_H_
#define VM_VMSELECTPLANNERSETTER_H_

namespace codablecash {
class SelectScanPlanner;
}
using namespace codablecash;

namespace alinous {

class VirtualMachine;

class VmSelectPlannerSetter {
public:
	VmSelectPlannerSetter(VirtualMachine* vm, SelectScanPlanner* planner);
	virtual ~VmSelectPlannerSetter();

private:
	VirtualMachine* vm;
};

} /* namespace alinous */

#endif /* VM_VMSELECTPLANNERSETTER_H_ */
