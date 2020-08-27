/*
 * ParenthesisScanTarget.h
 *
 *  Created on: 2020/08/09
 *      Author: iizuka
 */

#ifndef SCAN_TABLE_PARENTHESISSCANTARGET_H_
#define SCAN_TABLE_PARENTHESISSCANTARGET_H_

#include "scan_table/AbstractJoinScanTarget.h"

namespace codablecash {

class ParenthesisScanTarget : public AbstractJoinScanTarget {
public:
	ParenthesisScanTarget();
	virtual ~ParenthesisScanTarget();

	virtual const UnicodeString* toString() noexcept;

	void setInner(AbstractScanTableTarget* inner) noexcept;

	virtual void resolveTable(VirtualMachine* vm, SelectScanPlanner* planner);

private:
	AbstractScanTableTarget* inner;
};

} /* namespace codablecash */

#endif /* SCAN_TABLE_PARENTHESISSCANTARGET_H_ */
