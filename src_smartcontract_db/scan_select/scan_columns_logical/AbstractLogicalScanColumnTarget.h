/*
 * AbstractLogicalScanColumn.h
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_LOGICAL_ABSTRACTLOGICALSCANCOLUMNTARGET_H_
#define SCAN_COLUMNS_LOGICAL_ABSTRACTLOGICALSCANCOLUMNTARGET_H_

#include "scan_select/scan_columns/AbstractScanColumnsTarget.h"

namespace codablecash {

class AbstractLogicalScanColumnTarget : public AbstractScanColumnsTarget {
public:
	AbstractLogicalScanColumnTarget();
	virtual ~AbstractLogicalScanColumnTarget();
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_LOGICAL_ABSTRACTLOGICALSCANCOLUMNTARGET_H_ */
