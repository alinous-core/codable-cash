/*
 * AbstractColumnsIndexWrapper.h
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#ifndef SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_ABSTRACTCOLUMNSINDEXWRAPPER_H_
#define SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_ABSTRACTCOLUMNSINDEXWRAPPER_H_

namespace codablecash {

class AbstractColumnsIndexWrapper {
public:
	AbstractColumnsIndexWrapper();
	virtual ~AbstractColumnsIndexWrapper();

	virtual bool isOr() const noexcept {
		return false;
	}

	virtual int size() const noexcept = 0;
};

} /* namespace codablecash */

#endif /* SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_ABSTRACTCOLUMNSINDEXWRAPPER_H_ */
