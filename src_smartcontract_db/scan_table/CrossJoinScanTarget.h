/*
 * CrossJoinScanTarget.h
 *
 *  Created on: 2020/08/08
 *      Author: iizuka
 */

#ifndef SCAN_TABLE_CROSSJOINSCANTARGET_H_
#define SCAN_TABLE_CROSSJOINSCANTARGET_H_

#include "scan_table/AbstractJoinScanTarget.h"

namespace codablecash {

class CrossJoinScanTarget : public AbstractJoinScanTarget {
public:
	CrossJoinScanTarget();
	virtual ~CrossJoinScanTarget();

	virtual const UnicodeString* toString() noexcept;

	virtual IJoinLeftSource* getLeftSource(VirtualMachine* vm);
	virtual IJoinLeftSource* getRightSource(VirtualMachine* vm);
};

} /* namespace codablecash */

#endif /* SCAN_TABLE_CROSSJOINSCANTARGET_H_ */
