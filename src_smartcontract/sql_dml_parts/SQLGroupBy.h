/*
 * SQLGroupBy.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_PARTS_SQLGROUPBY_H_
#define SQL_DML_PARTS_SQLGROUPBY_H_

#include "sql/AbstractSQLPart.h"

namespace alinous {
class SQLHaving;

class SQLGroupBy : public AbstractSQLPart {
public:
	SQLGroupBy();
	virtual ~SQLGroupBy();

	void setHaving(SQLHaving* having) noexcept;
private:
	SQLHaving* having;
};

} /* namespace alinous */

#endif /* SQL_DML_PARTS_SQLGROUPBY_H_ */
