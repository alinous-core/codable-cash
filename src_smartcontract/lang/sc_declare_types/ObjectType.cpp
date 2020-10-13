/*
 * ObjectType.cpp
 *
 *  Created on: 2019/06/09
 *      Author: iizuka
 */

#include "lang/sc_declare_types/ObjectType.h"
#include "lang/sc_declare/PackageNameDeclare.h"
#include "base/UnicodeString.h"


namespace alinous {

ObjectType::ObjectType() : AbstractType(CodeElement::TYPE_OBJECT){
	this->packageName = nullptr;
	this->className = nullptr;
	this->str = nullptr;
}

ObjectType::~ObjectType() {
	delete this->packageName;
	delete this->className;
	delete this->str;
}

void ObjectType::setPackageName(PackageNameDeclare* packageName) noexcept {
	this->packageName = packageName;
}

int ObjectType::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractType::binarySize();

	total += sizeof(uint8_t);
	if(this->packageName != nullptr){
		total += this->packageName->binarySize();
	}

	total += stringSize(this->className);

	return total;
}

void ObjectType::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::TYPE_OBJECT);

	bool bl = this->packageName != nullptr;
	out->put(bl ? 1 : 0);
	if(bl){
		this->packageName->toBinary(out);
	}

	putString(out, this->className);
	AbstractType::toBinary(out);
}

void ObjectType::fromBinary(ByteBuffer* in) {
	uint8_t bl = in->get();
	if(bl > 0){
		CodeElement* element = CodeElement::createFromBinary(in);
		this->packageName = dynamic_cast<PackageNameDeclare*>(element);
	}

	this->className = getString(in);
	AbstractType::fromBinary(in);
}

const UnicodeString* ObjectType::toString() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");

		if(this->packageName != nullptr){
			this->str->append(this->packageName->getName());
			this->str->append(L".");
		}

		this->str->append(this->className);
	}

	return this->str;
}

void ObjectType::setName(UnicodeString* className) noexcept {
	this->className = className;
}

PackageNameDeclare* ObjectType::getPackageName() const noexcept {
	return this->packageName;
}

const UnicodeString* ObjectType::getClassName() const noexcept {
	return this->className;
}

} /* namespace alinous */
