/*
 * LeftOuterJoinTarget.h
 *
 *  Created on: 2020/08/08
 *      Author: iizuka
 */

#ifndef SCAN_TABLE_LEFTOUTERJOINTARGET_H_
#define SCAN_TABLE_LEFTOUTERJOINTARGET_H_

#include "scan_table/AbstractScanTableTarget.h"

namespace codablecash {

class LeftOuterJoinTarget : public AbstractScanTableTarget {
public:
	LeftOuterJoinTarget();
	virtual ~LeftOuterJoinTarget();
};

} /* namespace codablecash */

#endif /* SCAN_TABLE_LEFTOUTERJOINTARGET_H_ */
