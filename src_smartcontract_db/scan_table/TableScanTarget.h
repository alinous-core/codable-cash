/*
 * TableScanTarget.h
 *
 *  Created on: 2020/08/07
 *      Author: iizuka
 */

#ifndef SCAN_TABLE_TABLESCANTARGET_H_
#define SCAN_TABLE_TABLESCANTARGET_H_

#include "scan_table/AbstractScanTableTarget.h"



namespace codablecash {

class TableScanTarget : public AbstractScanTableTarget {
public:
	TableScanTarget();
	virtual ~TableScanTarget();

	virtual const UnicodeString* toString() noexcept;

private:

};

} /* namespace codablecash */

#endif /* SCAN_TABLE_TABLESCANTARGET_H_ */
