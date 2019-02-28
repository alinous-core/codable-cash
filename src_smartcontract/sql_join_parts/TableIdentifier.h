/*
 * TableIdentifier.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_TABLEIDENTIFIER_H_
#define SQL_EXPRESSION_TABLEIDENTIFIER_H_

#include "sql/AbstractJoinPart.h"

namespace alinous {
class UnicodeString;

class TableIdentifier : public AbstractJoinPart {
public:
	TableIdentifier();
	virtual ~TableIdentifier();

	void setSchema(UnicodeString* schema) noexcept;
	void setTableName(UnicodeString* tableName) noexcept;
private:
	UnicodeString* schema;
	UnicodeString* tableName;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_TABLEIDENTIFIER_H_ */
