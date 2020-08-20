/*
 * AbstractLogicalScanColumn.h
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_LOGICAL_ABSTRACTLOGICALSCANCOLUMNTARGET_H_
#define SCAN_COLUMNS_LOGICAL_ABSTRACTLOGICALSCANCOLUMNTARGET_H_

#include "scan_columns/AbstractScanColumns.h"

namespace codablecash {

class AbstractLogicalScanColumnTarget : public AbstractScanColumns {
public:
	AbstractLogicalScanColumnTarget();
	virtual ~AbstractLogicalScanColumnTarget();
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_LOGICAL_ABSTRACTLOGICALSCANCOLUMNTARGET_H_ */
