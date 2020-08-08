/*
 * AbstractScanTableTarget.h
 *
 *  Created on: 2020/08/07
 *      Author: iizuka
 */

#ifndef SCAN_TABLE_ABSTRACTSCANTABLETARGET_H_
#define SCAN_TABLE_ABSTRACTSCANTABLETARGET_H_

namespace alinous {
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class AbstractScanTableTarget {
public:
	AbstractScanTableTarget();
	virtual ~AbstractScanTableTarget();

	virtual const UnicodeString* toString() noexcept = 0;
};

} /* namespace codablecash */

#endif /* SCAN_TABLE_ABSTRACTSCANTABLETARGET_H_ */
