/*
 * InnerJoinScanTarget.h
 *
 *  Created on: 2020/08/08
 *      Author: iizuka
 */

#ifndef SCAN_TABLE_INNERJOINSCANTARGET_H_
#define SCAN_TABLE_INNERJOINSCANTARGET_H_

#include "scan_select/scan_table/AbstractJoinScanTarget.h"

namespace codablecash {

class InnerJoinScanTarget : public AbstractJoinScanTarget {
public:
	InnerJoinScanTarget();
	virtual ~InnerJoinScanTarget();

	virtual const UnicodeString* toString() noexcept;

	virtual AbstractScannerFactory* getScanFactory(VirtualMachine* vm, SelectScanPlanner* planner);
};

} /* namespace codablecash */

#endif /* SCAN_TABLE_INNERJOINSCANTARGET_H_ */
