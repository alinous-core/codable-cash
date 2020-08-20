/*
 * AbstractLogicalScanColumn.h
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_LOGICAL_ABSTRACTLOGICALSCANCOLUMN_H_
#define SCAN_COLUMNS_LOGICAL_ABSTRACTLOGICALSCANCOLUMN_H_

#include "scan_columns/AbstractScanColumns.h"

namespace codablecash {

class AbstractLogicalScanColumn : public AbstractScanColumns {
public:
	AbstractLogicalScanColumn();
	virtual ~AbstractLogicalScanColumn();
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_LOGICAL_ABSTRACTLOGICALSCANCOLUMN_H_ */
