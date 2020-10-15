/*
 * SQLJoin.cpp
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */
#include "lang_sql/sql_join_parts/SQLJoin.h"
#include "lang_sql/sql_join_parts/SQLJoinPart.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "scan_select/scan_planner/base/TablesHolder.h"
#include "scan_select/scan_planner/base/SelectScanPlanner.h"
#include "scan_select/scan_planner/base/ConditionsHolder.h"

#include "engine/CdbException.h"

#include "scan_select/scan_table/AbstractJoinScanTarget.h"
#include "scan_select/scan_table/LeftOuterJoinTarget.h"
#include "scan_select/scan_table/InnerJoinScanTarget.h"
#include "scan_select/scan_table/CrossJoinScanTarget.h"
#include "scan_select/scan_table/RightOuterJoinScanTarget.h"

#include "scan_select/scan_condition/base/AbstractScanConditionElement.h"
#include "scan_select/scan_condition/base/ScanConditionCast.h"


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

	AbstractJoinScanTarget* lastJoin = nullptr;
	AbstractScanTableTarget* target = nullptr;

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		SQLJoinPart* part = this->list.get(i);

		uint8_t joinType = part->getJoinType();
		AbstractJoinScanTarget* currentJoin = newScanTarget(joinType);
		tableHolder->push(currentJoin);

		if(lastJoin != nullptr){
			currentJoin->setLeft(lastJoin);
		}
		else{
			this->first->interpret(vm); // push
			target = tableHolder->pop();
			currentJoin->setLeft(target);
		}

		part->interpret(vm); // push
		target = tableHolder->pop();
		currentJoin->setRight(target);

		AbstractSQLExpression* exp = part->getExp();
		if(exp != nullptr){
			handleOnCondition(vm, planner, currentJoin, exp);
		}

		lastJoin = currentJoin;
		tableHolder->pop();
	}

	tableHolder->push(lastJoin);

	return nullptr;
}

void SQLJoin::handleOnCondition(VirtualMachine* vm, SelectScanPlanner* planner,
		AbstractJoinScanTarget* currentJoin, AbstractSQLExpression* exp) {
	exp->interpret(vm);

	ConditionsHolder* cholder = planner->getConditions();
	AbstractScanConditionElement* element = cholder->pop();

	AbstractScanCondition* cond = ScanConditionCast::toAbstractScanCondition(element, vm, this);
	currentJoin->setCondition(cond);
}

AbstractJoinScanTarget* SQLJoin::newScanTarget(uint8_t joinType) {
	AbstractJoinScanTarget* join = nullptr;
	switch(joinType){
	case SQLJoinPart::LEFT_OUTER_JOIN:
		join = new LeftOuterJoinTarget();
		break;
	case SQLJoinPart::RIGHT_OUTER_JOIN:
		join = new RightOuterJoinScanTarget();
		break;
	case SQLJoinPart::INNER_JOIN:
		join = new InnerJoinScanTarget();
		break;
	case SQLJoinPart::CROSS_JOIN:
		join = new CrossJoinScanTarget();
		break;
	default:
		throw new CdbException(L"wrong join type", __FILE__, __LINE__);
	}


	return join;
}

} /* namespace alinous */
