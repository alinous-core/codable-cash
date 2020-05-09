/*
 * ColumnTypeDescriptor.h
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#ifndef SQL_DDL_COLUMNTYPEDESCRIPTOR_H_
#define SQL_DDL_COLUMNTYPEDESCRIPTOR_H_

#include "sql/AbstractSQLPart.h"

namespace alinous {

class UnicodeString;
class AbstractSQLExpression;

class ColumnTypeDescriptor : public AbstractSQLPart {
public:
	ColumnTypeDescriptor();
	virtual ~ColumnTypeDescriptor();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	void setTypeName(UnicodeString* typeName) noexcept;
	void setLength(AbstractSQLExpression* length) noexcept;
private:
	UnicodeString* typeName;
	AbstractSQLExpression* length;

};

} /* namespace alinous */

#endif /* SQL_DDL_COLUMNTYPEDESCRIPTOR_H_ */
