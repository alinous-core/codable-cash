/*
 * EqualityScanColumnTarget.h
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_EXP_EQUALITYSCANCOLUMNTARGET_H_
#define SCAN_COLUMNS_EXP_EQUALITYSCANCOLUMNTARGET_H_

#include "scan_select/scan_columns/scan_columns_exp/AbstractExpressionScanColumnTarget.h"

namespace codablecash {

class EqualityScanColumnTarget : public AbstractExpressionScanColumnTarget {
public:
	EqualityScanColumnTarget();
	virtual ~EqualityScanColumnTarget();

	void setLeft(AbstractScanColumnsTarget* element) noexcept;
	void setRight(AbstractScanColumnsTarget* element) noexcept;

	virtual const UnicodeString* toStringCode() noexcept;

	virtual void resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner);

private:
	AbstractScanColumnsTarget* left;
	AbstractScanColumnsTarget* right;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_EXP_EQUALITYSCANCOLUMNTARGET_H_ */
