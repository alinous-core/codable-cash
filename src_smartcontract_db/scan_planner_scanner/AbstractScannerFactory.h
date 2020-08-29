/*
 * AbstractScannerFactory.h
 *
 *  Created on: 2020/08/28
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_ABSTRACTSCANNERFACTORY_H_
#define SCAN_PLANNER_SCANNER_ABSTRACTSCANNERFACTORY_H_

namespace alinous {
class VirtualMachine;
}
using namespace alinous;

namespace codablecash {


class IJoinLeftSource;
class IJoinRightSource;
class SelectScanPlanner;

class AbstractScannerFactory {
public:
	AbstractScannerFactory();
	virtual ~AbstractScannerFactory();


	virtual IJoinLeftSource* createScannerAsLeftSource(VirtualMachine* vm, SelectScanPlanner* planner) = 0;
	virtual IJoinRightSource* createScannerAsRightSource(VirtualMachine* vm, SelectScanPlanner* planner) = 0;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_ABSTRACTSCANNERFACTORY_H_ */
