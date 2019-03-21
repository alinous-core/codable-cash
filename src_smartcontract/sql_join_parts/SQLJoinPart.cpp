/*
 * SQLJoinPart.cpp
 *
 *  Created on: 2019/02/25
 *      Author: iizuka
 */

#include "sql_join_parts/SQLJoinPart.h"
#include "sql_join_parts/TableIdentifier.h"

namespace alinous {

SQLJoinPart::SQLJoinPart() : AbstractJoinPart(CodeElement::SQL_EXP_JOIN_PART) {
	this->joinType = 0;
	this->table = nullptr;
	this->exp = nullptr;
}

SQLJoinPart::~SQLJoinPart() {
	delete this->table;
	delete this->exp;
}

void SQLJoinPart::setJoinType(uint8_t joinType) noexcept {
	this->joinType = joinType;
}

void SQLJoinPart::setTable(AbstractJoinPart* table) noexcept {
	this->table = table;
}

void SQLJoinPart::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

int SQLJoinPart::binarySize() const {
	checkNotNull(this->table);
	int total = sizeof(uint16_t);

	total += sizeof(uint8_t);
	total += this->table->binarySize();

	total += sizeof(uint8_t);
	if(this->exp != nullptr){
		total += this->exp->binarySize();
	}

	return total;
}

void SQLJoinPart::toBinary(ByteBuffer* out) {
	checkNotNull(this->table);

	out->putShort(CodeElement::SQL_EXP_JOIN_PART);
	out->put(this->joinType);
	this->table->toBinary(out);

	out->put(this->exp != nullptr ? 1 : 0);
	if(this->exp != nullptr){
		this->exp->toBinary(out);
	}
}

void SQLJoinPart::fromBinary(ByteBuffer* in) {
	this->joinType = in->get();

	CodeElement* element = createFromBinary(in);
	checkIsJoinPart(element);
	this->table = dynamic_cast<AbstractJoinPart*>(element);

	int8_t bl = in->get();
	if(bl == 1){
		element = createFromBinary(in);
		checkIsSQLExp(element);
		this->exp = dynamic_cast<AbstractSQLExpression*>(element);
	}
}

} /* namespace alinous */
