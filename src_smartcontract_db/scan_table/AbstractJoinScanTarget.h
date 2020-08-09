/*
 * AbstractJoinScanTarget.h
 *
 *  Created on: 2020/08/09
 *      Author: iizuka
 */

#ifndef SCAN_TABLE_ABSTRACTJOINSCANTARGET_H_
#define SCAN_TABLE_ABSTRACTJOINSCANTARGET_H_

#include "scan_table/AbstractScanTableTarget.h"

namespace alinous{
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class AbstractJoinScanTarget : public AbstractScanTableTarget {
public:
	AbstractJoinScanTarget();
	virtual ~AbstractJoinScanTarget();

	void setLeft(AbstractScanTableTarget* left) noexcept;
	void setRight(AbstractScanTableTarget* right) noexcept;

protected:
	void resetStr() noexcept;

protected:
	AbstractScanTableTarget* left;
	AbstractScanTableTarget* right;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_TABLE_ABSTRACTJOINSCANTARGET_H_ */
