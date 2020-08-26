/*
 * SelectStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_dml/SelectStatement.h"
#include "sql_dml_parts/SQLFrom.h"
#include "sql_dml_parts/SQLWhere.h"
#include "sql_dml_parts/SQLGroupBy.h"
#include "sql_dml_parts/SQLOrderBy.h"
#include "sql_dml_parts/SQLLimitOffset.h"
#include "sql_dml_parts/SQLSelectTargetList.h"

#include "base/UnicodeString.h"

#include "sc_analyze_stack/AnalyzeStack.h"
#include "sc_analyze_stack/AnalyzeStackManager.h"
#include "sc_analyze_stack/AnalyzedStackReference.h"

#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"
#include "vm/VmSelectPlannerSetter.h"

#include "vm_trx/VmTransactionHandler.h"

#include "scan_planner/SelectScanPlanner.h"
#include "scan_planner/TablesHolder.h"

#include "sql/AbstractJoinPart.h"

#include "scan_table/AbstractScanTableTarget.h"

#include "instance_exception/ExceptionInterrupt.h"

namespace alinous {

SelectStatement::SelectStatement() : AbstractSQLStatement(CodeElement::DML_STMT_SELECT) {
	this->list = nullptr;
	this->from = nullptr;
	this->where = nullptr;
	this->groupBy = nullptr;
	this->orderBy = nullptr;
	this->limitOffset = nullptr;
	this->intoVar = nullptr;
	this->lastSchemaVersion = 0;
	this->planner = nullptr;
}

SelectStatement::~SelectStatement() {
	delete this->list;
	delete this->from;
	delete this->where;
	delete this->groupBy;
	delete this->orderBy;
	delete this->limitOffset;
	delete this->intoVar;
	delete this->planner;
}

void SelectStatement::preAnalyze(AnalyzeContext* actx) {
	if(this->list != nullptr){
		this->list->setParent(this);
		this->list->preAnalyze(actx);
	}

	this->from->setParent(this);
	AbstractJoinPart* tablePart = this->from->getTablePart();
	tablePart->preAnalyze(actx);

	if(this->where != nullptr){
		this->where->setParent(this);
		this->where->preAnalyze(actx);
	}
}

void SelectStatement::analyzeTypeRef(AnalyzeContext* actx) {
	if(this->list != nullptr){
		this->list->analyzeTypeRef(actx);
	}

	AbstractJoinPart* tablePart = this->from->getTablePart();
	tablePart->analyzeTypeRef(actx);

	if(this->where != nullptr){
		this->where->analyzeTypeRef(actx);
	}
}

void SelectStatement::analyze(AnalyzeContext* actx) {
	if(this->list != nullptr){
		this->list->analyze(actx);
	}

	AbstractJoinPart* tablePart = this->from->getTablePart();
	tablePart->analyze(actx);

	if(this->where != nullptr){
		this->where->analyze(actx);
	}

	AnalyzeStackManager* stackManager = actx->getAnalyzeStackManager();
	AnalyzeStack* stack = stackManager->top();

	//this->intoVar
	if(this->intoVar != nullptr){
		AnalyzedType at(AnalyzedType::TYPE_DOM);
		AnalyzedStackReference* ref = new AnalyzedStackReference(this->intoVar, &at);
		stack->addVariableDeclare(ref);
	}
}

void SelectStatement::setList(SQLSelectTargetList* list) noexcept {
	this->list = list;
}

void SelectStatement::setFrom(SQLFrom* from) noexcept {
	this->from = from;
}

void SelectStatement::setWhere(SQLWhere* where) noexcept {
	this->where = where;
}

void SelectStatement::setGroupBy(SQLGroupBy* groupBy) noexcept {
	this->groupBy = groupBy;
}

void SelectStatement::setOrderBy(SQLOrderBy* orderBy) noexcept {
	this->orderBy = orderBy;
}

void SelectStatement::setLimitOffset(SQLLimitOffset* limitOffset) noexcept {
	this->limitOffset = limitOffset;
}

void SelectStatement::setintoVar(UnicodeString* intoVar) noexcept {
	this->intoVar = intoVar;
}

int SelectStatement::binarySize() const {
	checkNotNull(this->list);
	checkNotNull(this->from);

	int total = sizeof(uint16_t);
	total += this->list->binarySize();
	total += this->from->binarySize();

	total += sizeof(uint8_t);
	if(this->where != nullptr){
		total += this->where->binarySize();
	}

	total += sizeof(uint8_t);
	if(this->groupBy != nullptr){
		total += this->groupBy->binarySize();
	}

	total += sizeof(uint8_t);
	if(this->orderBy != nullptr){
		total += this->orderBy->binarySize();
	}

	total += sizeof(uint8_t);
	if(this->limitOffset != nullptr){
		total += this->limitOffset->binarySize();
	}

	return total;
}

void SelectStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->list);
	checkNotNull(this->from);

	out->putShort(CodeElement::DML_STMT_SELECT);
	this->list->toBinary(out);
	this->from->toBinary(out);

	out->put(this->where != nullptr ? 1 : 0);
	if(this->where != nullptr){
		this->where->toBinary(out);
	}

	out->put(this->groupBy != nullptr ? 1 : 0);
	if(this->groupBy != nullptr){
		this->groupBy->toBinary(out);
	}

	out->put(this->orderBy != nullptr ? 1 : 0);
	if(this->orderBy != nullptr){
		this->orderBy->toBinary(out);
	}

	out->put(this->limitOffset != nullptr ? 1 : 0);
	if(this->limitOffset != nullptr){
		this->limitOffset->toBinary(out);
	}
}

void SelectStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::SQL_PART_SELECT_TARGET_LIST);
	this->list = dynamic_cast<SQLSelectTargetList*>(element);

	element = createFromBinary(in);
	checkKind(element, CodeElement::SQL_PART_FROM);
	this->from = dynamic_cast<SQLFrom*>(element);

	int8_t bl = in->get();
	if(bl == 1){
		 element = createFromBinary(in);
		 checkKind(element, CodeElement::SQL_PART_WHERE);
		 this->where = dynamic_cast<SQLWhere*>(element);
	}

	bl = in->get();
	if(bl == 1){
		 element = createFromBinary(in);
		 checkKind(element, CodeElement::SQL_PART_GROUP_BY);
		 this->groupBy = dynamic_cast<SQLGroupBy*>(element);
	}

	bl = in->get();
	if(bl == 1){
		 element = createFromBinary(in);
		 checkKind(element, CodeElement::SQL_PART_ORDER_BY);
		 this->orderBy = dynamic_cast<SQLOrderBy*>(element);
	}

	bl = in->get();
	if(bl == 1){
		 element = createFromBinary(in);
		 checkKind(element, CodeElement::SQL_PART_LIMIT_OFFSET);
		 this->limitOffset = dynamic_cast<SQLLimitOffset*>(element);
	}
}

void SelectStatement::init(VirtualMachine* vm) {
	this->list->init(vm);

	AbstractJoinPart* tablePart = this->from->getTablePart();
	tablePart->init(vm);

	if(this->where != nullptr){
		this->where->init(vm);
	}
}

void SelectStatement::interpret(VirtualMachine* vm) {
	VmTransactionHandler* trxHandler = vm->getTransactionHandler();

	uint64_t currentVer = trxHandler->getSchemaObjectVersionId();
	if(currentVer > this->lastSchemaVersion){
		try{
			buildPlanner(vm, currentVer);
		}
		catch(ExceptionInterrupt* e){
			delete e;
			return;
		}
	}

	this->planner->executeQuery(vm);

	// FIXME SQL statement
}

void SelectStatement::buildPlanner(VirtualMachine* vm, uint64_t currentVer) {
	delete this->planner;
	this->planner = new SelectScanPlanner();

	VmSelectPlannerSetter setter(vm, this->planner);

	// analyze column
	this->list->interpret(vm);

	// From part
	AbstractJoinPart* tablePart = this->from->getTablePart();
	tablePart->interpret(vm);
	TablesHolder* tableHolder = this->planner->getTablesHolder();
	if(!tableHolder->isEmpty()){
		AbstractScanTableTarget* target = tableHolder->pop();
		tableHolder->addScanTarget(target);
	}

	if(this->where != nullptr){
		this->where->interpret(vm);
	}

	this->planner->plan(vm);

	this->lastSchemaVersion = currentVer;
}

SQLSelectTargetList* SelectStatement::getSQLSelectTargetList() const noexcept {
	return this->list;
}

} /* namespace alinous */
