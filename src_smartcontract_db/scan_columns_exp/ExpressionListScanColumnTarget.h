/*
 * ExpressionListScanColumnTarget.h
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_EXP_EXPRESSIONLISTSCANCOLUMNTARGET_H_
#define SCAN_COLUMNS_EXP_EXPRESSIONLISTSCANCOLUMNTARGET_H_

#include "scan_columns_exp/AbstractExpressionScanColumnTarget.h"

#include "base/ArrayList.h"

namespace codablecash {

class ExpressionListScanColumnTarget: public AbstractExpressionScanColumnTarget {
public:
	ExpressionListScanColumnTarget();
	virtual ~ExpressionListScanColumnTarget();

	void addElement(AbstractScanColumnsTarget* val) noexcept;

	virtual const UnicodeString* toStringCode() noexcept;

private:
	ArrayList<AbstractScanColumnsTarget> list;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_EXP_EXPRESSIONLISTSCANCOLUMNTARGET_H_ */
