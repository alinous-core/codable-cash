/*
 * AdditiveExpressionScanColumnTarget.h
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_ARITHMETIC_ADDITIVEEXPRESSIONSCANCOLUMNTARGET_H_
#define SCAN_COLUMNS_ARITHMETIC_ADDITIVEEXPRESSIONSCANCOLUMNTARGET_H_

#include "scan_columns_exp/AbstractExpressionScanColumnTarget.h"

#include "base/ArrayList.h"
#include "base/RawArrayPrimitive.h"

#include <cstdint>

using namespace alinous;

namespace codablecash {

class AdditiveExpressionScanColumnTarget: public AbstractExpressionScanColumnTarget {
public:
	AdditiveExpressionScanColumnTarget();
	virtual ~AdditiveExpressionScanColumnTarget();

	void addOperand(AbstractScanColumnsTarget* vp) noexcept;
	void addOperator(uint8_t op) noexcept;

	virtual const UnicodeString* toStringCode() noexcept;

	virtual void resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner);

private:
	ArrayList<AbstractScanColumnsTarget> list;
	RawArrayPrimitive<uint8_t> operations;

};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_ARITHMETIC_ADDITIVEEXPRESSIONSCANCOLUMNTARGET_H_ */
