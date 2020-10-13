/*
 * ParenthesisScanColumnTarget.h
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_EXP_PARENTHESISSCANCOLUMNTARGET_H_
#define SCAN_COLUMNS_EXP_PARENTHESISSCANCOLUMNTARGET_H_

#include "scan_select/scan_columns_exp/AbstractExpressionScanColumnTarget.h"

namespace codablecash {

class ParenthesisScanColumnTarget: public AbstractExpressionScanColumnTarget {
public:
	ParenthesisScanColumnTarget();
	virtual ~ParenthesisScanColumnTarget();

	void setInnser(AbstractScanColumnsTarget* cond) noexcept;

	virtual const UnicodeString* toStringCode() noexcept;

	virtual void resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner);

private:
	AbstractScanColumnsTarget* cond;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_EXP_PARENTHESISSCANCOLUMNTARGET_H_ */
