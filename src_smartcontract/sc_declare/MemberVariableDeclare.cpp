/*
 * MemberVariableDeclare.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "sc_declare/MemberVariableDeclare.h"
#include "sc_declare/AccessControlDeclare.h"
#include "sc_declare_types/AbstractType.h"
#include "base/UnicodeString.h"

#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/AnalyzedClass.h"

#include "sc/exceptions.h"

namespace alinous {

MemberVariableDeclare::MemberVariableDeclare() : CodeElement(CodeElement::MEMBER_VARIABLE_DECLARE) {
	this->ctrl = nullptr;
	this->type = nullptr;
	this->_static = false;
	this->name = nullptr;
}

MemberVariableDeclare::~MemberVariableDeclare() {
	if(this->ctrl){
		delete this->ctrl;
	}
	if(this->type){
		delete this->type;
	}
	if(this->name){
		delete this->name;
	}
}


void MemberVariableDeclare::preAnalyze(AnalyzeContext* actx) {
	AnalyzedClass* aclass = actx->getAnalyzedClass(this);


}

void MemberVariableDeclare::analyze(AnalyzeContext* actx) {

}

void MemberVariableDeclare::setAccessControl(AccessControlDeclare* ctrl) noexcept {
	this->ctrl = ctrl;
}

void MemberVariableDeclare::setType(AbstractType* type) noexcept {
	this->type = type;
}

void MemberVariableDeclare::setStatic(bool s) noexcept {
	this->_static = s;
}

void MemberVariableDeclare::setName(UnicodeString* name) noexcept {
	this->name = name;
}


int MemberVariableDeclare::binarySize() const {
	checkNotNull(this->ctrl);
	checkNotNull(this->type);
	checkNotNull(this->name);

	int total = sizeof(uint16_t);

	total += sizeof(uint8_t);
	total += this->ctrl->binarySize();
	total += this->type->binarySize();
	total += stringSize(this->name);

	return total;
}

void MemberVariableDeclare::toBinary(ByteBuffer* out) {
	checkNotNull(this->ctrl);
	checkNotNull(this->type);
	checkNotNull(this->name);

	out->putShort(CodeElement::MEMBER_VARIABLE_DECLARE);
	out->put(this->_static ? (char)1 : (char)0);
	this->ctrl->toBinary(out);
	this->type->toBinary(out);
	putString(out, this->name);
}

void MemberVariableDeclare::fromBinary(ByteBuffer* in) {
	uint8_t bl = in->get();
	this->_static = (bl == 1);

	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::ACCESS_CONTROL_DECLARE);
	this->ctrl = dynamic_cast<AccessControlDeclare*>(element);

	element = createFromBinary(in);
	checkIsType(element);

	this->type = dynamic_cast<AbstractType*>(element);

	this->name = getString(in);
}

} /* namespace alinous */
