/*
 * ColumnIndexMatcher.cpp
 *
 *  Created on: 2020/08/16
 *      Author: iizuka
 */

#include "table/ColumnIndexMatcher.h"
#include "table/CdbTableColumn.h"
#include "table/CdbTableIndex.h"

#include "engine/CdbOid.h"

namespace codablecash {

ColumnIndexMatcher::ColumnIndexMatcher(CdbTableIndex* idx) {
	this->idx = idx;
	this->length = 0;
}

ColumnIndexMatcher::~ColumnIndexMatcher() {
	this->idx = nullptr;
}

void ColumnIndexMatcher::doMatch(const ArrayList<CdbOid>* columnOidlist) noexcept {
	const ArrayList<CdbTableColumn>* idxColumnList = this->idx->getColumns();

	int maxLoop = idxColumnList->size() < columnOidlist->size() ? idxColumnList->size() : columnOidlist->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbOid* targetOid = columnOidlist->get(i);
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
