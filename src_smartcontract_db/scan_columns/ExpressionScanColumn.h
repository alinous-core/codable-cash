/*
 * ExpressionScanColumn.h
 *
 *  Created on: 2020/08/19
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_EXPRESSIONSCANCOLUMN_H_
#define SCAN_COLUMNS_EXPRESSIONSCANCOLUMN_H_

#include "scan_columns/AbstractScanColumns.h"

namespace alinous {
class AbstractSQLExpression;
}
using namespace alinous;

namespace codablecash {

class ExpressionScanColumn : public AbstractScanColumns {
public:
	explicit ExpressionScanColumn(AbstractSQLExpression* exp);
	virtual ~ExpressionScanColumn();

private:
	AbstractSQLExpression* exp;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_EXPRESSIONSCANCOLUMN_H_ */
