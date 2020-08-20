/*
 * BetweenScanColumnTarget.h
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_EXP_BETWEENSCANCOLUMNTARGET_H_
#define SCAN_COLUMNS_EXP_BETWEENSCANCOLUMNTARGET_H_

#include "scan_columns_exp/AbstractExpressionScanColumnTarget.h"

namespace codablecash {

class BetweenScanColumnTarget : public AbstractExpressionScanColumnTarget {
public:
	BetweenScanColumnTarget();
	virtual ~BetweenScanColumnTarget();

	void setLeft(AbstractScanColumns* left) noexcept;
	void setStart(AbstractScanColumns* start) noexcept;
	void setEnd(AbstractScanColumns* end) noexcept;

private:
	AbstractScanColumns* left;
	AbstractScanColumns* start;
	AbstractScanColumns* end;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_EXP_BETWEENSCANCOLUMNTARGET_H_ */
