/*
 * AbstractScanColumns.h
 *
 *  Created on: 2020/08/19
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_ABSTRACTSCANCOLUMNSTARGET_H_
#define SCAN_COLUMNS_ABSTRACTSCANCOLUMNSTARGET_H_

namespace alinous {
class UnicodeString;
class VirtualMachine;
}
using namespace alinous;

namespace codablecash {

class SelectScanPlanner;

class AbstractScanColumnsTarget {
public:
	AbstractScanColumnsTarget();
	virtual ~AbstractScanColumnsTarget();

	void setAsName(const UnicodeString* asName) noexcept;

	virtual const UnicodeString* toStringCode() noexcept = 0;

	virtual void resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner) = 0;
protected:
	void resetStr() noexcept;

protected:
	UnicodeString* asName;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_ABSTRACTSCANCOLUMNSTARGET_H_ */
