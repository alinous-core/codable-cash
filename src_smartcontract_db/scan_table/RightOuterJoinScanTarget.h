/*
 * RightOuterJoinScanTarget.h
 *
 *  Created on: 2020/08/09
 *      Author: iizuka
 */

#ifndef SCAN_TABLE_RIGHTOUTERJOINSCANTARGET_H_
#define SCAN_TABLE_RIGHTOUTERJOINSCANTARGET_H_

#include "scan_table/LeftOuterJoinTarget.h"

namespace codablecash {

class RightOuterJoinScanTarget : public LeftOuterJoinTarget {
public:
	RightOuterJoinScanTarget();
	virtual ~RightOuterJoinScanTarget();

	virtual void setLeft(AbstractScanTableTarget* left) noexcept;
	virtual void setRight(AbstractScanTableTarget* right) noexcept;

	virtual const UnicodeString* toString() noexcept;
};

} /* namespace codablecash */

#endif /* SCAN_TABLE_RIGHTOUTERJOINSCANTARGET_H_ */
