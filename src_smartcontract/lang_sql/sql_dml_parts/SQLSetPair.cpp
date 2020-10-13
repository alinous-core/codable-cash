/*
 * SQLSetPair.cpp
 *
 *  Created on: 2019/02/22
 *      Author: iizuka
 */

#include "lang_sql/sql_dml_parts/SQLSetPair.h"

#include "lang_sql/sql_expression/SQLColumnIdentifier.h"
#include "lang_sql/sql/AbstractSQLExpression.h"

namespace alinous {

SQLSetPair::SQLSetPair() : AbstractSQLPart(CodeElement::SQL_PART_SET_PAIR) {
	this->colId = nullptr;
	this->exp = nullptr;
}

SQLSetPair::~SQLSetPair() {
	delete this->colId;
	delete this->exp;
}

void SQLSetPair::setColumn(SQLColumnIdentifier* colId) noexcept {
	this->colId = colId;
}

void SQLSetPair::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

int SQLSetPair::binarySize() const {
	checkNotNull(this->colId);
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->colId->binarySize();
	total += this->exp->binarySize();

	return total;
}

void SQLSetPair::toBinary(ByteBuffer* out) {
	checkNotNull(this->colId);
	checkNotNull(this->exp);

	out->putShort(CodeElement::SQL_PART_SET_PAIR);
	this->colId->toBinary(out);
	this->exp->toBinary(out);
}

void SQLSetPair::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::SQL_EXP_COLUMN_ID);
	this->colId = dynamic_cast<SQLColumnIdentifier*>(element);

	element = createFromBinary(in);
	checkIsSQLExp(element);
	this->exp = dynamic_cast<AbstractSQLExpression*>(element);
}

} /* namespace alinous */
