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
}
using namespace alinous;

namespace codablecash {

class AbstractScanColumnsTarget {
public:
	AbstractScanColumnsTarget();
	virtual ~AbstractScanColumnsTarget();

	void setAsName(const UnicodeString* asName) noexcept;

protected:
	void resetStr() noexcept;

protected:
	UnicodeString* asName;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_ABSTRACTSCANCOLUMNSTARGET_H_ */
