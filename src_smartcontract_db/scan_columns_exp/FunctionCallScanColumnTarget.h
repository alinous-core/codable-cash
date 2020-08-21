/*
 * FunctionCallScanColumn.h
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_EXP_FUNCTIONCALLSCANCOLUMNTARGET_H_
#define SCAN_COLUMNS_EXP_FUNCTIONCALLSCANCOLUMNTARGET_H_

#include "scan_columns_exp/AbstractExpressionScanColumnTarget.h"

#include "base/ArrayList.h"

namespace codablecash {

class FunctionCallScanColumnTarget : public AbstractExpressionScanColumnTarget {
public:
	FunctionCallScanColumnTarget();
	virtual ~FunctionCallScanColumnTarget();

	void setName(const UnicodeString* name) noexcept;

	void addArgument(AbstractScanColumnsTarget* arg) noexcept;

	virtual const UnicodeString* toStringCode() noexcept;

private:
	UnicodeString* name;
	ArrayList<AbstractScanColumnsTarget> arguments;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_EXP_FUNCTIONCALLSCANCOLUMNTARGET_H_ */
