/*
 * AbstractJoinScannerFactory.h
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_ABSTRACTJOINSCANNERFACTORY_H_
#define SCAN_PLANNER_SCANNER_ABSTRACTJOINSCANNERFACTORY_H_

#include "scan_select/scan_planner/scanner/factory/AbstractScannerFactory.h"

namespace codablecash {

class AbstractJoinCandidate;

class AbstractJoinScannerFactory : public AbstractScannerFactory {
public:
	explicit AbstractJoinScannerFactory(const ScanResultMetadata* metadata, const AbstractScanCondition* joinCondition);
	virtual ~AbstractJoinScannerFactory();

	void setLeft(AbstractScannerFactory* factory) noexcept;
	void setRight(AbstractScannerFactory* factory) noexcept;
	void setJoinCandidate(const AbstractJoinCandidate* joinCandidate) noexcept;

protected:
	AbstractScannerFactory* leftFactory;
	AbstractScannerFactory* rightFactory;

	AbstractJoinCandidate* joinCandidate;

	AbstractScanCondition* joinCondition; // Join Condition
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_ABSTRACTJOINSCANNERFACTORY_H_ */
