/*
 * ColumnIndexMatcher.cpp
 *
 *  Created on: 2020/08/16
 *      Author: iizuka
 */

#include "schema_table/table/ColumnIndexMatcher.h"
#include "schema_table/table/CdbTableColumn.h"
#include "schema_table/table/CdbTableIndex.h"

#include "engine/CdbOid.h"

namespace codablecash {

ColumnIndexMatcher::ColumnIndexMatcher(CdbTableIndex* idx) {
	this->idx = idx;
	this->length = 0;
}

ColumnIndexMatcher::~ColumnIndexMatcher() {
	this->idx = nullptr;
}

void ColumnIndexMatcher::doMatch(const ArrayList<const CdbOid>* columnOidlist) noexcept {
	const ArrayList<CdbTableColumn>* idxColumnList = this->idx->getColumns();

	int maxLoop = idxColumnList->size() < columnOidlist->size() ? idxColumnList->size() : columnOidlist->size();
	for(int i = 0; i != maxLoop; ++i){
		const CdbOid* targetOid = columnOidlist->get(i);
		CdbTableColumn* indexColumn = idxColumnList->get(i);

		if(targetOid->equals(indexColumn->getOid())){
			this->length++;
		}
		else{
			return;
		}
	}
}

} /* namespace codablecash */
