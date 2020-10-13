/*
 * MethodNameCollection.cpp
 *
 *  Created on: 2019/12/12
 *      Author: iizuka
 */

#include "engine/sc_analyze_functions/MethodNameCollection.h"

#include "engine/sc_analyze_functions/VTableMethodEntry.h"

namespace alinous {

MethodNameCollection::MethodNameCollection() {
}

MethodNameCollection::~MethodNameCollection() {

}

void MethodNameCollection::addMethodEntry(VTableMethodEntry* entry) noexcept {
	this->list.addElement(entry);
}

const ArrayList<VTableMethodEntry>* MethodNameCollection::getList() const noexcept {
	return &this->list;
}

} /* namespace alinous */
