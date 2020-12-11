/*
 * AbstractColumnsIndexWrapper.h
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#ifndef SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_ABSTRACTCOLUMNSINDEXWRAPPER_H_
#define SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_ABSTRACTCOLUMNSINDEXWRAPPER_H_

namespace alinous {
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class SchemaManager;
class CdbTableColumn;
class AbstractScanTableTarget;
class CdbTableIndex;

class AbstractColumnsIndexWrapper {
public:
	AbstractColumnsIndexWrapper(const AbstractColumnsIndexWrapper& inst);
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

	virtual AbstractColumnsIndexWrapper* clone() const noexcept = 0;

	virtual const UnicodeString* toCodeString() noexcept = 0;

	const AbstractScanTableTarget* getTarget() const {
		return target;
	}

	void setTarget(const AbstractScanTableTarget* target) {
		this->target = target;
	}

protected:
	void resetStr() noexcept;

protected:
	const AbstractScanTableTarget* target;
	CdbTableIndex* index;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_ABSTRACTCOLUMNSINDEXWRAPPER_H_ */
