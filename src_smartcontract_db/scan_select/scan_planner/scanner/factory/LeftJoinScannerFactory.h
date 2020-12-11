/*
 * LeftJoinScannerFactory.h
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_LEFTJOINSCANNERFACTORY_H_
#define SCAN_PLANNER_SCANNER_LEFTJOINSCANNERFACTORY_H_

#include "scan_select/scan_planner/scanner/factory/AbstractJoinScannerFactory.h"

namespace codablecash {

class LeftJoinScannerFactory : public AbstractJoinScannerFactory {
public:
	LeftJoinScannerFactory(const ScanResultMetadata* metadata, const AbstractScanCondition* joinCondition);
	virtual ~LeftJoinScannerFactory();

	virtual IJoinLeftSource* createScannerAsLeftSource(VirtualMachine* vm, SelectScanPlanner* planner);
	virtual IJoinRightSource* createScannerAsRightSource(VirtualMachine* vm, SelectScanPlanner* planner, const ScanJoinContext* joinContext);
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_LEFTJOINSCANNERFACTORY_H_ */
