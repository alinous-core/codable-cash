/*
 * ScanColumn.h
 *
 *  Created on: 2020/08/19
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_SCANCOLUMN_H_
#define SCAN_COLUMNS_SCANCOLUMN_H_

#include "scan_columns/AbstractScanColumns.h"

namespace codablecash {

class ScanColumn : public AbstractScanColumns {
public:
	ScanColumn();
	virtual ~ScanColumn();
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_SCANCOLUMN_H_ */
