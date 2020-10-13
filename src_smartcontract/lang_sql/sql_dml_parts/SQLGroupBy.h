/*
 * SQLGroupBy.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_PARTS_SQLGROUPBY_H_
#define SQL_DML_PARTS_SQLGROUPBY_H_

#include "lang_sql/sql/AbstractSQLPart.h"

namespace alinous {
class SQLColumnsList;
class SQLHaving;

class SQLGroupBy : public AbstractSQLPart {
public:
	SQLGroupBy();
	virtual ~SQLGroupBy();

	void setList(SQLColumnsList* list) noexcept;
	void setHaving(SQLHaving* having) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	SQLColumnsList* list;
	SQLHaving* having;
};

} /* namespace alinous */

#endif /* SQL_DML_PARTS_SQLGROUPBY_H_ */
