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

class SQLFrom : public AbstractSQLPart {
public:
	SQLFrom();
	virtual ~SQLFrom();

	void setTableId(TableIdentifier* tableId) noexcept;
private:
	TableIdentifier* tableId;
};

} /* namespace alinous */

#endif /* SQL_DML_PARTS_SQLFROM_H_ */
