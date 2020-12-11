/*
 * TableScannerFactory.h
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_TABLESCANNERFACTORY_H_
#define SCAN_PLANNER_SCANNER_TABLESCANNERFACTORY_H_

#include "scan_select/scan_planner/scanner/factory/AbstractScannerFactory.h"

namespace codablecash {

class AbstractIndexCandidate;

class TableScannerFactory : public AbstractScannerFactory {
public:
	explicit TableScannerFactory(const ScanResultMetadata* metadata, const AbstractIndexCandidate* indexCandidate);
	virtual ~TableScannerFactory();

	virtual IJoinLeftSource* createScannerAsLeftSource(VirtualMachine* vm, SelectScanPlanner* planner);
	virtual IJoinRightSource* createScannerAsRightSource(VirtualMachine* vm, SelectScanPlanner* planner, const ScanJoinContext* joinContext);

private:
	AbstractIndexCandidate* indexCandidate;

};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_TABLESCANNERFACTORY_H_ */
