/*
 * DdlColumnDescriptor.h
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#ifndef SQL_DDL_DDLCOLUMNDESCRIPTOR_H_
#define SQL_DDL_DDLCOLUMNDESCRIPTOR_H_

#include "sql/AbstractSQLPart.h"

namespace alinous {

class UnicodeString;
class ColumnTypeDescriptor;
class AbstractSQLExpression;

class DdlColumnDescriptor : public AbstractSQLPart {
public:
	DdlColumnDescriptor();
	virtual ~DdlColumnDescriptor();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	void setName(UnicodeString* name) noexcept;
	void setColumnType(ColumnTypeDescriptor* typeDesc) noexcept;
	void setNotNull(bool notNull) noexcept;
	void setUnique(bool unique) noexcept;
	void setDefaultValue(AbstractSQLExpression* defaultValue) noexcept;
private:
	UnicodeString* name;
	ColumnTypeDescriptor* typeDesc;
	bool notNull;
	bool unique;
	AbstractSQLExpression* defaultValue;
};

} /* namespace alinous */

#endif /* SQL_DDL_DDLCOLUMNDESCRIPTOR_H_ */
