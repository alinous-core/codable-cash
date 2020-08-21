/*
 * LikeExpression.h
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_EXP_LIKEEXPRESSIONSCANCOLUMNTARGET_H_
#define SCAN_COLUMNS_EXP_LIKEEXPRESSIONSCANCOLUMNTARGET_H_

#include "scan_columns_exp/AbstractExpressionScanColumnTarget.h"

namespace codablecash {

class LikeExpressionScanColumnTarget: public AbstractExpressionScanColumnTarget {
public:
	LikeExpressionScanColumnTarget();
	virtual ~LikeExpressionScanColumnTarget();

	void setLeft(AbstractScanColumns* left) noexcept;
	void setRight(AbstractScanColumns* right) noexcept;
	void setEscape(AbstractScanColumns* escape) noexcept;

private:
	AbstractScanColumns* left;
	AbstractScanColumns* right;
	AbstractScanColumns* escape;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_EXP_LIKEEXPRESSIONSCANCOLUMNTARGET_H_ */
