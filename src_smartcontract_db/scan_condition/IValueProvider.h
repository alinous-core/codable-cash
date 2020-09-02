/*
 * IValueProvider.h
 *
 *  Created on: 2020/07/21
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_IVALUEPROVIDER_H_
#define SCAN_CONDITION_IVALUEPROVIDER_H_

namespace alinous {
class VirtualMachine;
}
using namespace alinous;

namespace codablecash {

class SelectScanPlanner;

class IValueProvider {
public:
	IValueProvider();
	virtual ~IValueProvider();

	virtual void analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner){};
	virtual IValueProvider* clone() const noexcept = 0;


};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_IVALUEPROVIDER_H_ */
