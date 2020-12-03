/*
 * MultipleColumnIndex.cpp
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index_resolv/MultipleColumnIndex.h"

#include "scan_select/scan_planner/scanner/index_resolv/SingleColumnIndex.h"

namespace codablecash {

MultipleColumnIndex::MultipleColumnIndex() {

}

MultipleColumnIndex::~MultipleColumnIndex() {
	this->list.deleteElements();
}

bool MultipleColumnIndex::hasIndex(SchemaManager* schemaManager) {

	// TODO hasIndex
	return false;
}

int MultipleColumnIndex::size() const noexcept {
	return this->list.size();
}

void MultipleColumnIndex::add(SingleColumnIndex* idx) noexcept {
	this->list.addElement(idx);
}

} /* namespace codablecash */
