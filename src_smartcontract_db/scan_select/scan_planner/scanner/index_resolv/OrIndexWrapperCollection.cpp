/*
 * OrIndexWrapperCollection.cpp
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index_resolv/OrIndexWrapperCollection.h"
#include "scan_select/scan_planner/scanner/index_resolv/AbstractColumnsIndexWrapper.h"

#include "base/UnicodeString.h"
#include "base/ArrayList.h"


namespace codablecash {

OrIndexWrapperCollection::OrIndexWrapperCollection(const OrIndexWrapperCollection& inst) : AbstractColumnsIndexWrapper(inst) {
	int maxLoop = inst.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractColumnsIndexWrapper* index = inst.list.get(i);

		add(index->clone());
	}
}

OrIndexWrapperCollection::OrIndexWrapperCollection() {

}

OrIndexWrapperCollection::~OrIndexWrapperCollection() {
	this->list.deleteElements();
}

bool OrIndexWrapperCollection::hasIndex(SchemaManager* schemaManager) {
	int maxLoop = size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractColumnsIndexWrapper* index = this->list.get(i);

		if(!index->hasIndex(schemaManager)){
			return false;
		}
	}

	return true;
}

int OrIndexWrapperCollection::size() const noexcept {
	return this->list.size();
}

void OrIndexWrapperCollection::add(AbstractColumnsIndexWrapper* index) noexcept {
	this->list.addElement(index);
}

const UnicodeString* OrIndexWrapperCollection::toCodeString() noexcept {
	if(this->str == nullptr){
		makeCodeString();
	}

	return this->str;
}

void OrIndexWrapperCollection::makeCodeString() noexcept {
	this->str = new UnicodeString(L"");

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractColumnsIndexWrapper* index = this->list.get(i);

		if(i != 0){
			this->str->append(L" OR ");
		}

		const UnicodeString* s = index->toCodeString();
		this->str->append(s);
	}
}

AbstractColumnsIndexWrapper* OrIndexWrapperCollection::clone() const noexcept {
	return new OrIndexWrapperCollection(*this);
}


} /* namespace codablecash */
