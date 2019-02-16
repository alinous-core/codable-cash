/*
 * TableIdentifier.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_TABLEIDENTIFIER_H_
#define SQL_EXPRESSION_TABLEIDENTIFIER_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {
class UnicodeString;

class TableIdentifier : public AbstractSQLExpression {
public:
	TableIdentifier();
	virtual ~TableIdentifier();

	void setScheme(UnicodeString* scheme) noexcept;
	void setTableName(UnicodeString* tableName) noexcept;
private:
	UnicodeString* scheme;
	UnicodeString* tableName;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_TABLEIDENTIFIER_H_ */
