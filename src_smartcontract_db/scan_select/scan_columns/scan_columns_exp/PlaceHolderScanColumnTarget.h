/*
 * PlaceHolderScanColumnTarget.h
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_EXP_PLACEHOLDERSCANCOLUMNTARGET_H_
#define SCAN_COLUMNS_EXP_PLACEHOLDERSCANCOLUMNTARGET_H_

namespace alinous {
class AbstractExpression;
}
using namespace alinous;

#include "scan_select/scan_columns/scan_columns_exp/AbstractExpressionScanColumnTarget.h"

namespace codablecash {

class PlaceHolderScanColumnTarget: public AbstractExpressionScanColumnTarget {
public:
	explicit PlaceHolderScanColumnTarget(AbstractExpression* exp);
	virtual ~PlaceHolderScanColumnTarget();

	virtual const UnicodeString* toStringCode() noexcept;

	virtual void resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner);

private:
	AbstractExpression* exp;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_EXP_PLACEHOLDERSCANCOLUMNTARGET_H_ */
