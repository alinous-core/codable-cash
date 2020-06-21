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

namespace alinous {

SelectStatement::SelectStatement() : AbstractSQLStatement(CodeElement::DML_STMT_SELECT) {
	this->list = nullptr;
	this->from = nullptr;
	this->where = nullptr;
	this->groupBy = nullptr;
	this->orderBy = nullptr;
	this->limitOffset = nullptr;
	this->intoVar = nullptr;
}

SelectStatement::~SelectStatement() {
	delete this->list;
	delete this->from;
	delete this->where;
	delete this->groupBy;
	delete this->orderBy;
	delete this->limitOffset;
	delete this->intoVar;
}

void SelectStatement::preAnalyze(AnalyzeContext* actx) {

}

void SelectStatement::analyzeTypeRef(AnalyzeContext* actx) {
}

void SelectStatement::analyze(AnalyzeContext* actx) {

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

void SelectStatement::interpret(VirtualMachine* vm) {
	// FIXME SQL statement
}

} /* namespace alinous */
