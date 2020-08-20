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

class AbstractScanColumns;

class ScanColumnHolder {
public:
	ScanColumnHolder();
	virtual ~ScanColumnHolder();

	void push(AbstractScanColumns* column) noexcept;
//	AbstractScanColumns* top() const noexcept;
	AbstractScanColumns* pop() noexcept;

private:
	ArrayList<AbstractScanColumns> stack;
};

} /* namespace codablecash */

#endif /* SCAN_COLUMNS_SCANCOLUMNHOLDER_H_ */
