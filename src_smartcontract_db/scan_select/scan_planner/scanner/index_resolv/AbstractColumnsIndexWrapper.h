/*
 * AbstractColumnsIndexWrapper.h
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#ifndef SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_ABSTRACTCOLUMNSINDEXWRAPPER_H_
#define SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_ABSTRACTCOLUMNSINDEXWRAPPER_H_

namespace codablecash {

class SchemaManager;
class CdbTableColumn;
class AbstractScanTableTarget;
class CdbTableIndex;

class AbstractColumnsIndexWrapper {
public:
	AbstractColumnsIndexWrapper();
	virtual ~AbstractColumnsIndexWrapper();

	virtual bool isOr() const noexcept {
		return false;
	}
	virtual bool isRange() const noexcept {
		return false;
	}

	virtual int size() const noexcept = 0;

	virtual bool hasIndex(SchemaManager* schemaManager) = 0;

	const AbstractScanTableTarget* getTarget() const {
		return target;
	}

	void setTarget(const AbstractScanTableTarget* target) {
		this->target = target;
	}

protected:
	const AbstractScanTableTarget* target;
	CdbTableIndex* index;
};

} /* namespace codablecash */

#endif /* SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_ABSTRACTCOLUMNSINDEXWRAPPER_H_ */
