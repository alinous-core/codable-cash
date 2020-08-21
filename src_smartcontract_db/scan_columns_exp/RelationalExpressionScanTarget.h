/*
 * RelationalExpressionScanTarget.h
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_EXP_RELATIONALEXPRESSIONSCANTARGET_H_
#define SCAN_COLUMNS_EXP_RELATIONALEXPRESSIONSCANTARGET_H_

#include "scan_columns_exp/AbstractExpressionScanColumnTarget.h"
#include <cstdint>

namespace codablecash {

class RelationalExpressionScanTarget: public AbstractExpressionScanColumnTarget {
public:
	RelationalExpressionScanTarget();
	virtual ~RelationalExpressionScanTarget();

	void setLeft(AbstractScanColumns* element) noexcept;
	void setRight(AbstractScanColumns* element) noexcept;
	void setOp(uint8_t op) noexcept;

private:
	AbstractScanColumns* left;
	AbstractScanColumns* right;

	uint8_t op;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_EXP_RELATIONALEXPRESSIONSCANTARGET_H_ */
