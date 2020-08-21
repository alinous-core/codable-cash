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

	void setLeft(AbstractScanColumnsTarget* left) noexcept;
	void setRight(AbstractScanColumnsTarget* right) noexcept;
	void setEscape(AbstractScanColumnsTarget* escape) noexcept;

private:
	AbstractScanColumnsTarget* left;
	AbstractScanColumnsTarget* right;
	AbstractScanColumnsTarget* escape;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_EXP_LIKEEXPRESSIONSCANCOLUMNTARGET_H_ */
