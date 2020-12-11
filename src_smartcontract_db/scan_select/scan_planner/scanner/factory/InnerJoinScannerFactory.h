/*
 * InnerJoinFactory.h
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_INNERJOINSCANNERFACTORY_H_
#define SCAN_PLANNER_SCANNER_INNERJOINSCANNERFACTORY_H_

#include "scan_select/scan_planner/scanner/factory/AbstractJoinScannerFactory.h"

namespace codablecash {

class InnerJoinScannerFactory : public AbstractJoinScannerFactory {
public:
	InnerJoinScannerFactory(const ScanResultMetadata* metadata, const AbstractScanCondition* joinCondition);
	virtual ~InnerJoinScannerFactory();

	virtual IJoinLeftSource* createScannerAsLeftSource(VirtualMachine* vm, SelectScanPlanner* planner);
	virtual IJoinRightSource* createScannerAsRightSource(VirtualMachine* vm, SelectScanPlanner* planner, const ScanJoinContext* joinContext);
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_INNERJOINSCANNERFACTORY_H_ */
