/*
 * AbstractColumnParam.h
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_PARAMS_ABSTRACTCOLUMNPARAM_H_
#define SCAN_COLUMNS_PARAMS_ABSTRACTCOLUMNPARAM_H_

#include "scan_select/scan_columns/AbstractScanColumnsTarget.h"

namespace codablecash {

class AbstractColumnParam : public AbstractScanColumnsTarget {
public:
	AbstractColumnParam();
	virtual ~AbstractColumnParam();

	virtual void resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner){}
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_PARAMS_ABSTRACTCOLUMNPARAM_H_ */
