/*
 * SQLHaving.cpp
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#include "lang_sql/sql_dml_parts/SQLHaving.h"
#include "lang_sql/sql/AbstractSQLExpression.h"

namespace alinous {

SQLHaving::SQLHaving() : AbstractSQLPart(CodeElement::SQL_PART_HAVING) {
	this->exp = nullptr;
}

SQLHaving::~SQLHaving() {
	delete this->exp;
}

void alinous::SQLHaving::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

int SQLHaving::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void SQLHaving::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::SQL_PART_HAVING);
	this->exp->toBinary(out);
}

void SQLHaving::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->exp = dynamic_cast<AbstractSQLExpression*>(element);
}

} /* namespace alinous */
