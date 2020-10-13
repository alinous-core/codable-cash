/*
 * LeftOuterJoinTarget.h
 *
 *  Created on: 2020/08/08
 *      Author: iizuka
 */

#ifndef SCAN_TABLE_LEFTOUTERJOINTARGET_H_
#define SCAN_TABLE_LEFTOUTERJOINTARGET_H_

#include "scan_select/scan_table/AbstractJoinScanTarget.h"

namespace codablecash {

class LeftOuterJoinTarget : public AbstractJoinScanTarget {
public:
	LeftOuterJoinTarget();
	virtual ~LeftOuterJoinTarget();

	virtual const UnicodeString* toString() noexcept;
	virtual AbstractScannerFactory* getScanFactory(VirtualMachine* vm, SelectScanPlanner* planner);
};

} /* namespace codablecash */

#endif /* SCAN_TABLE_LEFTOUTERJOINTARGET_H_ */
