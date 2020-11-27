/*
 * SingleColumnIndex.h
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#ifndef SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_SINGLECOLUMNINDEX_H_
#define SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_SINGLECOLUMNINDEX_H_

#include "scan_select/scan_planner/scanner/index_resolv/AbstractColumnsIndexWrapper.h"

namespace codablecash {

class CdbTableColumn;

class SingleColumnIndex : public AbstractColumnsIndexWrapper {
public:
	SingleColumnIndex();
	virtual ~SingleColumnIndex();

	virtual int size() const noexcept;

	const CdbTableColumn* getColumn() const noexcept {
		return column;
	}

	void setColumn(const CdbTableColumn* column) noexcept {
		this->column = column;
	}

private:
	const CdbTableColumn* column;
};

} /* namespace codablecash */

#endif /* SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_SINGLECOLUMNINDEX_H_ */
