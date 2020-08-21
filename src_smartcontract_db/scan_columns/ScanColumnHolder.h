/*
 * ScanColumnHolder.h
 *
 *  Created on: 2020/08/19
 *      Author: iizuka
 */

#ifndef SCAN_COLUMNS_SCANCOLUMNHOLDER_H_
#define SCAN_COLUMNS_SCANCOLUMNHOLDER_H_

#include "base/ArrayList.h"

using alinous::ArrayList;

namespace codablecash {

class AbstractScanColumnsTarget;

class ScanColumnHolder {
public:
	ScanColumnHolder();
	virtual ~ScanColumnHolder();

	void push(AbstractScanColumnsTarget* column) noexcept;
//	AbstractScanColumns* top() const noexcept;
	AbstractScanColumnsTarget* pop() noexcept;

private:
	ArrayList<AbstractScanColumnsTarget> stack;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_SCANCOLUMNHOLDER_H_ */
