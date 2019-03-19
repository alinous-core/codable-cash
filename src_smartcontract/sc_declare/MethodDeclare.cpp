/*
 * MethodDeclare.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "sc_declare/MethodDeclare.h"
#include "sc_declare/AccessControlDeclare.h"
#include "sc_declare/ArgumentsListDeclare.h"
#include "sc_declare_types/AbstractType.h"
#include "sc_statement/StatementBlock.h"
#include "base/UnicodeString.h"

namespace alinous {

MethodDeclare::MethodDeclare() : CodeElement(CodeElement::METHOD_DECLARE) {
	this->_static = false;
	this->name = nullptr;
	this->ctrl = nullptr;
	this->type = nullptr;
	this->args = nullptr;
	this->block = nullptr;
}

MethodDeclare::~MethodDeclare() {
	if(this->name){
		delete this->name;
	}
	if(this->ctrl){
		delete this->ctrl;
	}
	if(this->type){
		delete this->type;
	}
	if(this->args){
		delete this->args;
	}
	if(this->block){
		delete this->block;
	}
}

void MethodDeclare::setStatic(bool s) noexcept {
	this->_static = s;
}

void MethodDeclare::setAccessControl(AccessControlDeclare* ctrl) noexcept {
	this->ctrl = ctrl;
}

void MethodDeclare::setType(AbstractType* type) noexcept {
	this->type = type;
}

void MethodDeclare::setName(UnicodeString* name) noexcept {
	this->name = name;
}

void MethodDeclare::setArguments(ArgumentsListDeclare* args) noexcept {
	this->args = args;
}

void MethodDeclare::setBlock(StatementBlock* block) noexcept {
	this->block = block;
}

int MethodDeclare::binarySize() const {
	checkNotNull(this->name);
	checkNotNull(this->ctrl);
	checkNotNull(this->type);
	checkNotNull(this->args);

	int total = sizeof(uint16_t);
	total += sizeof(char);
	total += stringSize(this->name);
	total += this->ctrl->binarySize();
	total += this->type->binarySize();
	total += this->args->binarySize();

	total += sizeof(uint8_t);
	if(this->block != nullptr){
		total += this->block->binarySize();
	}

	return total;
}

void MethodDeclare::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);
	checkNotNull(this->ctrl);
	checkNotNull(this->type);
	checkNotNull(this->args);

	out->putShort(CodeElement::METHOD_DECLARE);

	out->put(this->_static ? (char)1 : (char)0);
	putString(out, this->name);
	this->ctrl->toBinary(out);
	this->type->toBinary(out);
	this->args->toBinary(out);

	out->put(this->block != nullptr ? (uint8_t)1 : (uint8_t)0);
	if(this->block != nullptr){
		this->block->toBinary(out);
	}

}

void MethodDeclare::fromBinary(ByteBuffer* in) {
	uint8_t bl = in->get();
	this->_static = (bl == 1);

	this->name = getString(in);

	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::ACCESS_CONTROL_DECLARE);
	this->ctrl = dynamic_cast<AccessControlDeclare*>(element);

	element = createFromBinary(in);
	checkIsType(element);
	this->type = dynamic_cast<AbstractType*>(element);

	element = createFromBinary(in);
	checkKind(element, CodeElement::ARGUMENTS_LIST_DECLARE);
	this->args = dynamic_cast<ArgumentsListDeclare*>(element);

	bl = in->get();
	if(bl == 1){
		element = createFromBinary(in);
		checkKind(element, CodeElement::STMT_BLOCK);
		this->block = dynamic_cast<StatementBlock*>(element);
	}
}

} /* namespace alinous */
