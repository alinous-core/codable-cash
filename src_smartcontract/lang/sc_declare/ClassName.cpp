/*
 * ClassName.cpp
 *
 *  Created on: 2019/06/19
 *      Author: iizuka
 */

#include "lang/sc_declare/ClassName.h"

#include "base/UnicodeString.h"

namespace alinous {

ClassName::ClassName() : CodeElement(CodeElement::CLASS_NAME) {
	this->fqn = nullptr;
}

ClassName::~ClassName() {
	delete this->fqn;
}

void ClassName::addStr(const char* str) noexcept {
	UnicodeString ustr(str);

	if(this->fqn == nullptr){
		this->fqn = new UnicodeString(L"");
	}
	this->fqn->append(&ustr);
}

void ClassName::addStr(const UnicodeString* str) noexcept {
	if(this->fqn == nullptr){
		this->fqn = new UnicodeString(L"");
	}
	this->fqn->append(str);
}

const UnicodeString* ClassName::getName() noexcept {
	return this->fqn;
}

int ClassName::binarySize() const {
	checkNotNull(this->fqn);

	int total = sizeof(uint16_t);
	total += stringSize(this->fqn);

	return total;
}

void ClassName::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::CLASS_NAME);
	putString(out, this->fqn);
}

void ClassName::fromBinary(ByteBuffer* in) {
	this->fqn = getString(in);
}

} /* namespace alinous */
