/*
 * SQLSelectTargetList.cpp
 *
 *  Created on: 2019/02/23
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLSelectTargetList.h"
#include "sql_dml_parts/SQLSelectTarget.h"

#include "sc_analyze/AnalyzeContext.h"

#include "vm/VirtualMachine.h"

#include "instance/AbstractVmInstance.h"
namespace alinous {

SQLSelectTargetList::SQLSelectTargetList() : AbstractSQLPart(CodeElement::SQL_PART_SELECT_TARGET_LIST) {
}

SQLSelectTargetList::~SQLSelectTargetList() {
	this->list.deleteElements();
}

void SQLSelectTargetList::addTarget(SQLSelectTarget* target) noexcept {
	this->list.addElement(target);
}

int SQLSelectTargetList::binarySize() const {
	int total = sizeof(uint16_t);

	total += sizeof(uint32_t);
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		SQLSelectTarget* target = this->list.get(i);
		total += target->binarySize();
	}

	return total;
}

void SQLSelectTargetList::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_PART_SELECT_TARGET_LIST);

	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		SQLSelectTarget* target = this->list.get(i);
		target->toBinary(out);
	}
}

void SQLSelectTargetList::fromBinary(ByteBuffer* in) {
	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = createFromBinary(in);
		checkKind(element, CodeElement::SQL_PART_SELECT_TARGET);
		SQLSelectTarget* target = dynamic_cast<SQLSelectTarget*>(element);

		this->list.addElement(target);
	}
}

void SQLSelectTargetList::preAnalyze(AnalyzeContext* actx) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		SQLSelectTarget* target = this->list.get(i);

		target->setParent(this);
		target->preAnalyze(actx);
	}
}

void SQLSelectTargetList::analyzeTypeRef(AnalyzeContext* actx) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		SQLSelectTarget* target = this->list.get(i);
		target->analyzeTypeRef(actx);
	}
}

void SQLSelectTargetList::analyze(AnalyzeContext* actx) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		SQLSelectTarget* target = this->list.get(i);
		target->analyze(actx);
	}
}

void SQLSelectTargetList::init(VirtualMachine* vm) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		SQLSelectTarget* target = this->list.get(i);
		target->init(vm);
	}
}

AbstractVmInstance* SQLSelectTargetList::interpret(VirtualMachine* vm) {

}


} /* namespace alinous */
