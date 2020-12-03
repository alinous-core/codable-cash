/*
 * OrIndexWrapperCollection.h
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#ifndef SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_ORINDEXWRAPPERCOLLECTION_H_
#define SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_ORINDEXWRAPPERCOLLECTION_H_

#include "scan_select/scan_planner/scanner/index_resolv/AbstractColumnsIndexWrapper.h"
#include "base/ArrayList.h"

using alinous::ArrayList;

namespace codablecash {

class OrIndexWrapperCollection : public AbstractColumnsIndexWrapper {
public:
	OrIndexWrapperCollection();
	virtual ~OrIndexWrapperCollection();

	virtual bool isOr() const noexcept {
		return true;
	}
	virtual int size() const noexcept;
	virtual bool hasIndex(SchemaManager* schemaManager);

	void add(AbstractColumnsIndexWrapper* index) noexcept;

private:
	ArrayList<AbstractColumnsIndexWrapper> list;
};

} /* namespace codablecash */

#endif /* SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_ORINDEXWRAPPERCOLLECTION_H_ */
