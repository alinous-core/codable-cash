/*
 * AbstractExpressionScanColumnTarget.h
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_EXP_ABSTRACTEXPRESSIONSCANCOLUMNTARGET_H_
#define SCAN_COLUMNS_EXP_ABSTRACTEXPRESSIONSCANCOLUMNTARGET_H_

#include "scan_columns/AbstractScanColumns.h"

namespace codablecash {

class AbstractExpressionScanColumnTarget : public AbstractScanColumns {
public:
	AbstractExpressionScanColumnTarget();
	virtual ~AbstractExpressionScanColumnTarget();
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_EXP_ABSTRACTEXPRESSIONSCANCOLUMNTARGET_H_ */
