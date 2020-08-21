/*
 * NotScanColumnTarget.h
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_LOGICAL_NOTSCANCOLUMNTARGET_H_
#define SCAN_COLUMNS_LOGICAL_NOTSCANCOLUMNTARGET_H_

#include "scan_columns_exp/AbstractExpressionScanColumnTarget.h"

namespace codablecash {

class NotScanColumnTarget : public AbstractExpressionScanColumnTarget {
public:
	NotScanColumnTarget();
	virtual ~NotScanColumnTarget();

	void setCond(AbstractScanColumnsTarget* cond) noexcept;

	virtual const UnicodeString* toStringCode() noexcept;

private:
	AbstractScanColumnsTarget* cond;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_LOGICAL_NOTSCANCOLUMNTARGET_H_ */
