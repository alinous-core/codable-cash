/*
 * SQLFrom.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_PARTS_SQLFROM_H_
#define SQL_DML_PARTS_SQLFROM_H_

#include "sql/AbstractSQLPart.h"

namespace alinous {
class TableIdentifier;
class AbstractJoinPart;

class SQLFrom : public AbstractSQLPart {
public:
	SQLFrom();
	virtual ~SQLFrom();

	void setTable(AbstractJoinPart* tableId) noexcept;

private:
	AbstractJoinPart* tableId;
};

} /* namespace alinous */

#endif /* SQL_DML_PARTS_SQLFROM_H_ */
