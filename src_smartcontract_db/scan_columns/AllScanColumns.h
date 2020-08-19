/*
 * AllScanColumns.h
 *
 *  Created on: 2020/08/19
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_ALLSCANCOLUMNS_H_
#define SCAN_COLUMNS_ALLSCANCOLUMNS_H_

#include "scan_columns/AbstractScanColumns.h"

namespace codablecash {

class AllScanColumns : public AbstractScanColumns {
public:
	AllScanColumns();
	virtual ~AllScanColumns();
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_ALLSCANCOLUMNS_H_ */
