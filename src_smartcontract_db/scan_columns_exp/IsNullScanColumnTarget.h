/*
 * IsNullScanColumnTarget.h
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_EXP_ISNULLSCANCOLUMNTARGET_H_
#define SCAN_COLUMNS_EXP_ISNULLSCANCOLUMNTARGET_H_

#include "scan_columns_exp/AbstractExpressionScanColumnTarget.h"

namespace codablecash {

class IsNullScanColumnTarget : public AbstractExpressionScanColumnTarget {
public:
	IsNullScanColumnTarget();
	virtual ~IsNullScanColumnTarget();

	void setCondition(AbstractScanColumns* cond) noexcept;
	void setIsNull(bool notnull) noexcept;

private:
	AbstractScanColumns* cond;
	bool notnull;

};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_EXP_ISNULLSCANCOLUMNTARGET_H_ */
