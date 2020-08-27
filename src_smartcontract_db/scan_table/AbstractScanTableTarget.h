/*
 * AbstractScanTableTarget.h
 *
 *  Created on: 2020/08/07
 *      Author: iizuka
 */

#ifndef SCAN_TABLE_ABSTRACTSCANTABLETARGET_H_
#define SCAN_TABLE_ABSTRACTSCANTABLETARGET_H_

namespace alinous {
class UnicodeString;
class VirtualMachine;
}
using namespace alinous;

namespace codablecash {

class IJoinLeftSource;
class IJoinRightSource;
class SelectScanPlanner;

class AbstractScanTableTarget {
public:
	AbstractScanTableTarget();
	virtual ~AbstractScanTableTarget();

	virtual const UnicodeString* toString() noexcept = 0;

	virtual void resolveTable(VirtualMachine* vm, SelectScanPlanner* planner) = 0;
};

} /* namespace codablecash */

#endif /* SCAN_TABLE_ABSTRACTSCANTABLETARGET_H_ */
