/*
 * AbstractJoinScannerFactory.h
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_ABSTRACTJOINSCANNERFACTORY_H_
#define SCAN_PLANNER_SCANNER_ABSTRACTJOINSCANNERFACTORY_H_

#include "scan_planner_scanner/AbstractScannerFactory.h"

namespace codablecash {

class AbstractJoinScannerFactory : public AbstractScannerFactory {
public:
	explicit AbstractJoinScannerFactory(const ScanResultMetadata* metadata);
	virtual ~AbstractJoinScannerFactory();

};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_ABSTRACTJOINSCANNERFACTORY_H_ */
