/*
 * ColumnIdentifierColumn.h
 *
 *  Created on: 2020/07/21
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_PARAMS_COLUMNIDENTIFIERSCANPARAM_H_
#define SCAN_CONDITION_PARAMS_COLUMNIDENTIFIERSCANPARAM_H_

#include "scan_condition_params/AbstractScanConditionParameter.h"

namespace alinous {
class SQLColumnIdentifier;
}
using namespace alinous;

namespace codablecash {

class CdbTableColumn;

class ColumnIdentifierScanParam : public AbstractScanConditionParameter {
public:
	explicit ColumnIdentifierScanParam(SQLColumnIdentifier* sqlColId);
	virtual ~ColumnIdentifierScanParam();

	virtual const UnicodeString* toStringCode() noexcept;

	virtual void analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner);
private:
	const SQLColumnIdentifier* sqlColId;
	CdbTableColumn* cdbColumn;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_PARAMS_COLUMNIDENTIFIERSCANPARAM_H_ */
