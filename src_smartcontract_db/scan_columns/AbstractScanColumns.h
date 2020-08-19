/*
 * AbstractScanColumns.h
 *
 *  Created on: 2020/08/19
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_ABSTRACTSCANCOLUMNS_H_
#define SCAN_COLUMNS_ABSTRACTSCANCOLUMNS_H_

namespace alinous {
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class AbstractScanColumns {
public:
	AbstractScanColumns();
	virtual ~AbstractScanColumns();

	void setAsName(const UnicodeString* asName) noexcept;
private:
	UnicodeString* asName;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_ABSTRACTSCANCOLUMNS_H_ */
