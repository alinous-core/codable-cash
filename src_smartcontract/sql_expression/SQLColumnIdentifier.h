/*
 * SQLColumnIdentifier.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLCOLUMNIDENTIFIER_H_
#define SQL_EXPRESSION_SQLCOLUMNIDENTIFIER_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {
class UnicodeString;

class SQLColumnIdentifier : public AbstractSQLExpression {
public:
	SQLColumnIdentifier();
	virtual ~SQLColumnIdentifier();

	void setSchema(UnicodeString* schema) noexcept;
	void setTableName(UnicodeString* tableName) noexcept;
	void setColumnName(UnicodeString* columnName) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	UnicodeString* schema;
	UnicodeString* tableName;
	UnicodeString* columnName;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLCOLUMNIDENTIFIER_H_ */
