/*
 * SQLJoin.cpp
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */
#include "sql_join_parts/SQLJoin.h"
#include "sql_join_parts/SQLJoinPart.h"

#include "sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "scan_planner/TablesHolder.h"
#include "scan_planner/SelectScanPlanner.h"

#include "engine/CdbException.h"

#include "scan_table/AbstractJoinScanTarget.h"
#include "scan_table/LeftOuterJoinTarget.h"
#include "scan_table/InnerJoinScanTarget.h"
#include "scan_table/CrossJoinScanTarget.h"

namespace alinous {

SQLJoin::SQLJoin() : AbstractJoinPart(CodeElement::SQL_EXP_JOIN) {
	this->first = nullptr;
}

SQLJoin::~SQLJoin() {
	this->list.deleteElements();
	delete this->first;
}

void SQLJoin::setFirst(AbstractJoinPart* first) noexcept {
	this->first = first;
}

void SQLJoin::addJoinPart(SQLJoinPart* part) noexcept {
	this->list.addElement(part);
}

int SQLJoin::binarySize() const {
	checkNotNull(this->first);

	int total = sizeof(uint16_t);
	total += this->first->binarySize();

	total += sizeof(uint32_t);
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		SQLJoinPart* part = this->list.get(i);
		total += part->binarySize();
	}

	return total;
}

void SQLJoin::toBinary(ByteBuffer* out) {
	checkNotNull(this->first);

	out->putShort(CodeElement::SQL_EXP_JOIN);
	this->first->toBinary(out);

	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		SQLJoinPart* part = this->list.get(i);
		part->toBinary(out);
	}
}

void SQLJoin::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsJoinPart(element);
	this->first = dynamic_cast<AbstractJoinPart*>(element);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		element = createFromBinary(in);
		checkKind(element, CodeElement::SQL_EXP_JOIN_PART);
		SQLJoinPart* part = dynamic_cast<SQLJoinPart*>(element);

		this->list.addElement(part);
	}
}

void SQLJoin::preAnalyze(AnalyzeContext* actx) {
	this->first->setParent(this);
	this->first->preAnalyze(actx);

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		SQLJoinPart* part = this->list.get(i);

		part->setParent(this);
		part->preAnalyze(actx);
	}
}

void SQLJoin::analyzeTypeRef(AnalyzeContext* actx) {
	this->first->analyzeTypeRef(actx);

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		SQLJoinPart* part = this->list.get(i);

		part->analyzeTypeRef(actx);
	}
}

void SQLJoin::analyze(AnalyzeContext* actx) {
	this->first->analyze(actx);

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		SQLJoinPart* part = this->list.get(i);

		part->analyze(actx);
	}
}

AnalyzedType SQLJoin::getType(AnalyzeContext* actx) {
	return AnalyzedType();
}

void SQLJoin::init(VirtualMachine* vm) {
	this->first->init(vm);

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		SQLJoinPart* part = this->list.get(i);

		part->init(vm);
	}
}

AbstractVmInstance* SQLJoin::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	TablesHolder* tableHolder = planner->getTablesHolder();

	AbstractJoinPart* lastPart = this->first;

	lastPart->interpret(vm);
	AbstractScanTableTarget* lastTarget = tableHolder->pop();

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		SQLJoinPart* part = this->list.get(i);

		part->interpret(vm);
		AbstractScanTableTarget* target = tableHolder->pop();

		uint8_t joinType = part->getJoinType();
		lastTarget = SQLJoin::newScanTarget(lastTarget, target, joinType);



		if(i == 0){
			tableHolder->push(target);
		}
	}

	return nullptr; // FIXME SQLJoin
}

AbstractJoinScanTarget* SQLJoin::newScanTarget(AbstractScanTableTarget* left, AbstractScanTableTarget* right, uint8_t joinType) {
	AbstractJoinScanTarget* join = nullptr;
	switch(joinType){
	case SQLJoinPart::LEFT_OUTER_JOIN:
		join = new LeftOuterJoinTarget();
		join->setLeft(left);
		join->setRight(right);
		break;
	case SQLJoinPart::RIGHT_OUTER_JOIN:
		join = new LeftOuterJoinTarget();
		join->setLeft(right);
		join->setRight(left);
		break;
	case SQLJoinPart::INNER_JOIN:
		join = new InnerJoinScanTarget();
		join->setLeft(left);
		join->setRight(right);
		break;
	case SQLJoinPart::CROSS_JOIN:
		join = new CrossJoinScanTarget();
		join->setLeft(left);
		join->setRight(right);
		break;
		break;
	default:
		delete right;
		throw new CdbException(L"wrong join type", __FILE__, __LINE__);
	}


	return join;
}

} /* namespace alinous */
