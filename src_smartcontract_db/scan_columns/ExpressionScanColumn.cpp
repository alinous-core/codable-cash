/*
 * ExpressionScanColumn.cpp
 *
 *  Created on: 2020/08/19
 *      Author: iizuka
 */

#include "scan_columns/ExpressionScanColumn.h"

namespace codablecash {

ExpressionScanColumn::ExpressionScanColumn(AbstractSQLExpression* exp) {
	this->exp = exp;
}

ExpressionScanColumn::~ExpressionScanColumn() {
	this->exp = nullptr;
}

} /* namespace codablecash */
