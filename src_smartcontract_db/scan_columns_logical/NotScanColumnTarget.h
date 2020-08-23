/*
 * NotScanColumnTarget.h
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_LOGICAL_NOTSCANCOLUMNTARGET_H_
#define SCAN_COLUMNS_LOGICAL_NOTSCANCOLUMNTARGET_H_

#include "scan_columns_logical/AbstractLogicalScanColumnTarget.h"

namespace codablecash {

class NotScanColumnTarget : public AbstractLogicalScanColumnTarget {
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
