/*
 * TableScannerFactory.h
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_TABLESCANNERFACTORY_H_
#define SCAN_PLANNER_SCANNER_TABLESCANNERFACTORY_H_

#include "scan_planner_scanner/AbstractScannerFactory.h"

namespace codablecash {

class TableScannerFactory : public AbstractScannerFactory {
public:
	explicit TableScannerFactory(const ScanResultMetadata* metadata);
	virtual ~TableScannerFactory();
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_TABLESCANNERFACTORY_H_ */
