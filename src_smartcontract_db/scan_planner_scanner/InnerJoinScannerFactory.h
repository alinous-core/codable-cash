/*
 * InnerJoinFactory.h
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_INNERJOINSCANNERFACTORY_H_
#define SCAN_PLANNER_SCANNER_INNERJOINSCANNERFACTORY_H_

#include "scan_planner_scanner/AbstractJoinScannerFactory.h"

namespace codablecash {

class InnerJoinScannerFactory : public AbstractJoinScannerFactory {
public:
	InnerJoinScannerFactory(const ScanResultMetadata* metadata);
	virtual ~InnerJoinScannerFactory();
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_INNERJOINSCANNERFACTORY_H_ */
