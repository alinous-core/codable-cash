/*
 * AbstractColumnParam.h
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_PARAMS_ABSTRACTCOLUMNPARAM_H_
#define SCAN_COLUMNS_PARAMS_ABSTRACTCOLUMNPARAM_H_

#include "scan_columns/AbstractScanColumns.h"

namespace codablecash {

class AbstractColumnParam : public AbstractScanColumns {
public:
	AbstractColumnParam();
	virtual ~AbstractColumnParam();
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_PARAMS_ABSTRACTCOLUMNPARAM_H_ */
