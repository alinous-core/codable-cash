/*
 * FunctionCallScanColumn.h
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_EXP_FUNCTIONCALLSCANCOLUMNTARGET_H_
#define SCAN_COLUMNS_EXP_FUNCTIONCALLSCANCOLUMNTARGET_H_

#include "scan_columns_exp/AbstractExpressionScanColumnTarget.h"

namespace codablecash {

class FunctionCallScanColumnTarget : public AbstractExpressionScanColumnTarget {
public:
	FunctionCallScanColumnTarget();
	virtual ~FunctionCallScanColumnTarget();
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_EXP_FUNCTIONCALLSCANCOLUMNTARGET_H_ */
