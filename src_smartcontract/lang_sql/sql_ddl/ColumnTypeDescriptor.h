/*
 * ColumnTypeDescriptor.h
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#ifndef SQL_DDL_COLUMNTYPEDESCRIPTOR_H_
#define SQL_DDL_COLUMNTYPEDESCRIPTOR_H_

#include "lang_sql/sql/AbstractSQLPart.h"

namespace alinous {

class UnicodeString;
class AbstractSQLExpression;
class AnalyzeContext;

class ColumnTypeDescriptor : public AbstractSQLPart {
public:
	static const UnicodeString TYPE_BYTE;
	static const UnicodeString TYPE_SHORT;
	static const UnicodeString TYPE_INT;
	static const UnicodeString TYPE_LONG;
	static const UnicodeString TYPE_VARCHAR;
	static const UnicodeString TYPE_TEXT;

	ColumnTypeDescriptor();
	virtual ~ColumnTypeDescriptor();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	void analyze(AnalyzeContext* actx);

	void setTypeName(UnicodeString* typeName) noexcept;
	void setLength(AbstractSQLExpression* length) noexcept;

	uint8_t toCdbValueType() const noexcept;

	const UnicodeString* getTypeName() const noexcept {
		return this->typeName;
	}

	AbstractSQLExpression* getLengthExp() const noexcept {
		return this->length;
	}
private:
	UnicodeString* typeName;
	AbstractSQLExpression* length;

};

} /* namespace alinous */

#endif /* SQL_DDL_COLUMNTYPEDESCRIPTOR_H_ */
