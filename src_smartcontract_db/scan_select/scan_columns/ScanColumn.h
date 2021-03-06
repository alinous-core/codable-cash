/*
 * ScanColumn.h
 *
 *  Created on: 2020/08/19
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_SCANCOLUMN_H_
#define SCAN_COLUMNS_SCANCOLUMN_H_

#include "scan_select/scan_columns/AbstractScanColumnsTarget.h"

namespace alinous {
class SQLColumnIdentifier;
}
using namespace alinous;

namespace codablecash {

class ScanColumn : public AbstractScanColumnsTarget {
public:
	explicit ScanColumn(const SQLColumnIdentifier* sqlColumnId);
	virtual ~ScanColumn();

	virtual const UnicodeString* toStringCode() noexcept;

	virtual void resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner);

private:
	const SQLColumnIdentifier* sqlColumnId;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_SCANCOLUMN_H_ */
