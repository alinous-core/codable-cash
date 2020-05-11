/*
 * SchemaBinary.cpp
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#include "schema/SchemaBinary.h"

#include "base/UnicodeString.h"

#include "base_io/ByteBuffer.h"


namespace codablecash {

SchemaBinary::SchemaBinary() {

}

SchemaBinary::~SchemaBinary() {
	this->list.deleteElements();
}

void SchemaBinary::addSchemaName(const UnicodeString* name) noexcept {
	this->list.addElement(new UnicodeString(name));
}

int SchemaBinary::binarySize() const noexcept {
	int total = 0;

	total += sizeof(uint32_t);

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* name = this->list.get(i);

		total += stringSize(name);
	}

	return total;
}

void SchemaBinary::toBinary(ByteBuffer* out) const {
	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* name = this->list.get(i);

		putString(out, name);
	}
}

void SchemaBinary::fromBinary(ByteBuffer* in) {
	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* name = getString(in);
		this->list.addElement(name);
	}
}

int SchemaBinary::stringSize(UnicodeString* str) const noexcept {
	return sizeof(uint32_t) + str->length() * sizeof(uint16_t);
}

void SchemaBinary::putString(ByteBuffer* out, UnicodeString* str) const noexcept {
	uint32_t maxLoop = str->length();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		wchar_t ch = str->get(i);
		out->putChar(ch);
	}
}

UnicodeString* SchemaBinary::getString(ByteBuffer* in) const noexcept {
	UnicodeString* ret = new UnicodeString(L"");
	uint32_t maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		wchar_t ch = in->getChar();
		ret->append(ch);
	}

	return ret;
}

} /* namespace codablecash */
