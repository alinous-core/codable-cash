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
class ScanTargetNameResolver;
class AbstractScanTableTarget;

class ColumnIdentifierScanParam : public AbstractScanConditionParameter {
public:
	ColumnIdentifierScanParam(const ColumnIdentifierScanParam& inst);
	explicit ColumnIdentifierScanParam(SQLColumnIdentifier* sqlColId);
	virtual ~ColumnIdentifierScanParam();

	virtual const UnicodeString* toStringCode() noexcept;

	virtual void analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner);

	virtual AbstractScanConditionParameter* clone() const noexcept;

private:
	bool resolveAlias(const UnicodeString* tableAlias, ScanTargetNameResolver* aliasResolver);
private:
	const SQLColumnIdentifier* sqlColId;

	AbstractScanTableTarget* target;
	CdbTableColumn* cdbColumn;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_PARAMS_COLUMNIDENTIFIERSCANPARAM_H_ */
