/*
 * AndLogicalScanColumn.h
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_LOGICAL_ANDLOGICALSCANCOLUMNTARGET_H_
#define SCAN_COLUMNS_LOGICAL_ANDLOGICALSCANCOLUMNTARGET_H_

#include "scan_columns/AbstractScanColumns.h"

#include "base/ArrayList.h"


using namespace alinous;

namespace codablecash {

class AndLogicalScanColumnTarget : public AbstractScanColumns {
public:
	AndLogicalScanColumnTarget();
	virtual ~AndLogicalScanColumnTarget();

	void addCondition(AbstractScanColumns* cond) noexcept;

private:
	ArrayList<AbstractScanColumns> list;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_LOGICAL_ANDLOGICALSCANCOLUMNTARGET_H_ */
