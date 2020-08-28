/*
 * OrlScanColumnTarget.h
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_LOGICAL_ORSCANCOLUMNTARGET_H_
#define SCAN_COLUMNS_LOGICAL_ORSCANCOLUMNTARGET_H_

#include "scan_columns_logical/AbstractLogicalScanColumnTarget.h"

#include "base/ArrayList.h"

namespace codablecash {

class OrScanColumnTarget: public AbstractLogicalScanColumnTarget {
public:
	OrScanColumnTarget();
	virtual ~OrScanColumnTarget();

	void addCondition(AbstractScanColumnsTarget* cond) noexcept;

	virtual const UnicodeString* toStringCode() noexcept;

	virtual void resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner);

private:
	ArrayList<AbstractScanColumnsTarget> list;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_LOGICAL_ORSCANCOLUMNTARGET_H_ */
