/*
 * AnalyzedType.cpp
 *
 *  Created on: 2019/06/11
 *      Author: iizuka
 */

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzedClass.h"

#include "base/UnicodeString.h"

namespace alinous {

AnalyzedType::AnalyzedType(uint8_t type) {
	this->type = type;
	this->aclazz = nullptr;
	this->str = nullptr;
}

AnalyzedType::AnalyzedType(AnalyzedClass* clazz) {
	this->type = TYPE_OBJECT;
	this->aclazz = clazz;
	this->str = nullptr;
}

AnalyzedType::AnalyzedType(const AnalyzedType& obj) {
	this->type = obj.type;
	this->aclazz = obj.aclazz;
	this->str = nullptr;
}

AnalyzedType::AnalyzedType() {
	this->type = TYPE_NULL;
	this->aclazz = nullptr;
	this->str = nullptr;
}

AnalyzedType::~AnalyzedType() {
	this->aclazz = nullptr;
}

AnalyzedClass* AnalyzedType::getAnalyzedClass() const noexcept {
	return this->aclazz;
}

uint8_t AnalyzedType::getType() const noexcept {
	return this->type;
}

const UnicodeString* AnalyzedType::stringName() noexcept {
	if(this->str == nullptr){
		makeStringName();
	}
	return this->str;
}

void AnalyzedType::makeStringName() noexcept{
	switch(this->type){
	case TYPE_BOOL:
		this->str = new UnicodeString(L"boolean");
		break;
	case TYPE_BYTE:
		this->str = new UnicodeString(L"byte");
		break;
	case TYPE_CHAR:
		this->str = new UnicodeString(L"char");
		break;
	case TYPE_SHORT:
		this->str = new UnicodeString(L"short");
		break;
	case TYPE_INT:
		this->str = new UnicodeString(L"int");
		break;
	case TYPE_LONG:
		this->str = new UnicodeString(L"long");
		break;
	case TYPE_STRING:
		this->str = new UnicodeString(L"String");
		break;
	case TYPE_VOID:
		this->str = new UnicodeString(L"void");
		break;
	case TYPE_OBJECT:
		makeObjectString();
		break;
	default:
		this->str = new UnicodeString(L"null");
		break;
	}

}

void AnalyzedType::makeObjectString() noexcept {
	if(this->aclazz == nullptr){
		this->str = new UnicodeString(L"null");
		return;
	}

	const UnicodeString* name = this->aclazz->toString();
	this->str = new UnicodeString(name);
}

} /* namespace alinous */
