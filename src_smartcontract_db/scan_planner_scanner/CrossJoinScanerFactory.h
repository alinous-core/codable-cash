/*
 * CrossJoinScanerTarget.h
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CROSSJOINSCANERFACTORY_H_
#define SCAN_PLANNER_SCANNER_CROSSJOINSCANERFACTORY_H_

#include "scan_planner_scanner/AbstractJoinScannerFactory.h"

namespace codablecash {

class CrossJoinScanerFactory : public AbstractJoinScannerFactory {
public:
	CrossJoinScanerFactory();
	virtual ~CrossJoinScanerFactory();
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CROSSJOINSCANERFACTORY_H_ */
