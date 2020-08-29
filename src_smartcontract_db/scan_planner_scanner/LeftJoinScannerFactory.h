/*
 * LeftJoinScannerFactory.h
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_LEFTJOINSCANNERFACTORY_H_
#define SCAN_PLANNER_SCANNER_LEFTJOINSCANNERFACTORY_H_

#include "scan_planner_scanner/AbstractJoinScannerFactory.h"

namespace codablecash {

class LeftJoinScannerFactory : public AbstractJoinScannerFactory {
public:
	LeftJoinScannerFactory(const ScanResultMetadata* metadata);
	virtual ~LeftJoinScannerFactory();
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_LEFTJOINSCANNERFACTORY_H_ */
