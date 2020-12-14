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

class CdbTable;
class TableStore;
class AbstractColumnsIndexWrapper;
class CdbTransaction;

class TableScannerFactory : public AbstractScannerFactory {
public:
	explicit TableScannerFactory(const CdbTable* table, const ScanResultMetadata* metadata, AbstractColumnsIndexWrapper* indexCandidate);
	virtual ~TableScannerFactory();

	virtual IJoinLeftSource* createScannerAsLeftSource(VirtualMachine* vm, SelectScanPlanner* planner);
	virtual IJoinRightSource* createScannerAsRightSource(VirtualMachine* vm, SelectScanPlanner* planner, const ScanJoinContext* joinContext);

private:
	IJoinLeftSource* createIndexScannerAsLeftSource(VirtualMachine* vm, SelectScanPlanner* planner, TableStore* tableStore, CdbTransaction* trx);

private:
	AbstractColumnsIndexWrapper* indexCandidate;
	const CdbTable* table;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_TABLESCANNERFACTORY_H_ */
