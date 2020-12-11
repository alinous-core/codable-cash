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

class IValueProvider;
class CdbTableColumn;
class AbstractScanTableTarget;

class SingleColumnIndex : public AbstractColumnsIndexWrapper {
public:
	SingleColumnIndex();
	virtual ~SingleColumnIndex();

	const CdbTableColumn* getColumn() const noexcept {
		return column;
	}
	void setColumn(const CdbTableColumn* column) noexcept {
		this->column = column;
	}

	virtual int size() const noexcept;

	virtual AbstractColumnsIndexWrapper* clone() const noexcept;

	bool isBottomEq() const noexcept {
		return bottomEq;
	}

	void setBottomEq(bool bottomEq) noexcept {
		this->bottomEq = bottomEq;
	}

	bool isTopEq() const noexcept {
		return topEq;
	}

	void setTopEq(bool topEq) noexcept {
		this->topEq = topEq;
	}

	const IValueProvider* getTopValue() const noexcept {
		return topValue;
	}

	void setTopValue(const IValueProvider* topValue) noexcept {
		this->topValue = topValue;
	}

	const IValueProvider* getValue() const noexcept {
		return value;
	}

	void setValue(const IValueProvider* value) noexcept {
		this->value = value;
	}

	virtual bool isRange() const noexcept;
	void setRange(bool range) noexcept;

	virtual bool hasIndex(SchemaManager* schemaManager);

	virtual const UnicodeString* toCodeString() noexcept;

private:
	void makeRangeString() noexcept;
	void makeString() noexcept;

private:
	const CdbTableColumn* column;

	const IValueProvider* topValue;
	bool topEq;

	const IValueProvider* value;
	bool bottomEq;

	bool range;
};

} /* namespace codablecash */

#endif /* SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_SINGLECOLUMNINDEX_H_ */
