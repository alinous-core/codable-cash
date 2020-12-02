/*
 * MultipleColumnIndex.h
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#ifndef SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_MULTIPLECOLUMNINDEX_H_
#define SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_MULTIPLECOLUMNINDEX_H_

#include "scan_select/scan_planner/scanner/index_resolv/AbstractColumnsIndexWrapper.h"

namespace codablecash {

class MultipleColumnIndex : public AbstractColumnsIndexWrapper {
public:
	MultipleColumnIndex();
	virtual ~MultipleColumnIndex();

	virtual bool hasIndex(SchemaManager* schemaManager);
};

} /* namespace codablecash */

#endif /* SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_RESOLV_MULTIPLECOLUMNINDEX_H_ */
