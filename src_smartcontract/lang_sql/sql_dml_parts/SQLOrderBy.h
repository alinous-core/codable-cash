/*
 * SQLOrderBy.h
 *
 *  Created on: 2019/02/23
 *      Author: iizuka
 */

#ifndef SQL_DML_PARTS_SQLORDERBY_H_
#define SQL_DML_PARTS_SQLORDERBY_H_

#include "lang_sql/sql/AbstractSQLPart.h"

namespace alinous {

class SQLColumnsList;

class SQLOrderBy : public AbstractSQLPart {
public:
	SQLOrderBy();
	virtual ~SQLOrderBy();

	void setList(SQLColumnsList* list) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	SQLColumnsList* list;
};

} /* namespace alinous */

#endif /* SQL_DML_PARTS_SQLORDERBY_H_ */
