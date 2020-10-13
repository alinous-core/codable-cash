/*
 * NameSegments.cpp
 *
 *  Created on: 2020/05/02
 *      Author: iizuka
 */

#include "engine/sc_analyze/NameSegments.h"

#include "base/UnicodeString.h"


namespace alinous {

NameSegments::NameSegments() {
	this->list = new ArrayList<UnicodeString>();
	this->str = nullptr;
}

NameSegments::~NameSegments() {
	this->list->deleteElements();
	delete this->list;

	delete this->str;
}

void NameSegments::addSegment(const UnicodeString* seg) noexcept {
	UnicodeString* name = new UnicodeString(seg);
	this->list->addElement(name);
}

const UnicodeString* NameSegments::toString() noexcept {
	delete this->str;
	this->str = new UnicodeString(L"");

	int maxLoop = this->list->size();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* seg = this->list->get(i);

		if(i > 0){
			this->str->append(L".");
		}
		this->str->append(seg);
	}

	return this->str;
}

int NameSegments::length() const noexcept {
	return this->list->size();
}

void NameSegments::removeTop() noexcept {
	int topIndex = this->list->size() - 1;

	delete this->list->remove(topIndex);
}

} /* namespace alinous */
