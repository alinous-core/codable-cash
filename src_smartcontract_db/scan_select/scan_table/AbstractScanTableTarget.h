/*
 * AbstractScanTableTarget.h
 *
 *  Created on: 2020/08/07
 *      Author: iizuka
 */

#ifndef SCAN_TABLE_ABSTRACTSCANTABLETARGET_H_
#define SCAN_TABLE_ABSTRACTSCANTABLETARGET_H_

#include "base/ArrayList.h"

namespace alinous {
class UnicodeString;
class VirtualMachine;
}
using namespace alinous;

namespace codablecash {

class SelectScanPlanner;
class AbstractScannerFactory;
class ScanResultMetadata;
class CdbTable;
class CdbTableColumn;
class AbstractScanTableTarget;

typedef struct __ScanTableColumnParam {
	const CdbTable* table;
	const CdbTableColumn* column;
	const AbstractScanTableTarget* target;
} ScanTableColumnParam;

class AbstractScanTableTarget {
public:
	AbstractScanTableTarget();
	virtual ~AbstractScanTableTarget();

	virtual const UnicodeString* toString() noexcept = 0;

	virtual void resolveTable(VirtualMachine* vm, SelectScanPlanner* planner) = 0;
	virtual void collectScanTargets(VirtualMachine* vm, SelectScanPlanner* planner, ArrayList<AbstractScanTableTarget>* list) = 0;
	virtual AbstractScannerFactory* getScanFactory(VirtualMachine* vm, SelectScanPlanner* planner) = 0;
	virtual bool hasTarget(const AbstractScanTableTarget* target) const noexcept = 0;

	virtual ScanTableColumnParam* findTableColumns(const UnicodeString* colName) const = 0;

	const ScanResultMetadata* getMetadata() const noexcept {
		return metadata;
	}

protected:
	ScanResultMetadata* metadata;
};

} /* namespace codablecash */

#endif /* SCAN_TABLE_ABSTRACTSCANTABLETARGET_H_ */
