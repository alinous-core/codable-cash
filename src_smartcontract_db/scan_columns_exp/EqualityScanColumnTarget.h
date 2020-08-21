/*
 * EqualityScanColumnTarget.h
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_EXP_EQUALITYSCANCOLUMNTARGET_H_
#define SCAN_COLUMNS_EXP_EQUALITYSCANCOLUMNTARGET_H_

#include "scan_columns_exp/AbstractExpressionScanColumnTarget.h"

namespace codablecash {

class EqualityScanColumnTarget : public AbstractExpressionScanColumnTarget {
public:
	EqualityScanColumnTarget();
	virtual ~EqualityScanColumnTarget();

	void setLeft(AbstractScanColumns* element) noexcept;
	void setRight(AbstractScanColumns* element) noexcept;

private:
	AbstractScanColumns* left;
	AbstractScanColumns* right;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_EXP_EQUALITYSCANCOLUMNTARGET_H_ */
