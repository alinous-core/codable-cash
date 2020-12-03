/*
 * OrIndexWrapperCollection.cpp
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index_resolv/OrIndexWrapperCollection.h"

namespace codablecash {

OrIndexWrapperCollection::OrIndexWrapperCollection() {

}

OrIndexWrapperCollection::~OrIndexWrapperCollection() {
	this->list.deleteElements();
}

bool OrIndexWrapperCollection::hasIndex(SchemaManager* schemaManager) {
	return false;
}

int OrIndexWrapperCollection::size() const noexcept {
	return this->list.size();
}

void OrIndexWrapperCollection::add(AbstractColumnsIndexWrapper* index) noexcept {
	this->list.addElement(index);
}

} /* namespace codablecash */
