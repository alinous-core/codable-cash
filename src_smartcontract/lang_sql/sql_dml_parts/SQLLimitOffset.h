/*
 * SQLLimitOffset.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_PARTS_SQLLIMITOFFSET_H_
#define SQL_DML_PARTS_SQLLIMITOFFSET_H_

#include "lang_sql/sql/AbstractSQLPart.h"

namespace alinous {
class AbstractSQLExpression;

class SQLLimitOffset : public AbstractSQLPart {
public:
	SQLLimitOffset();
	virtual ~SQLLimitOffset();

	void setLimit(AbstractSQLExpression* limit) noexcept;
	void setOffset(AbstractSQLExpression* offset) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	AbstractSQLExpression* limit;
	AbstractSQLExpression* offset;
};

} /* namespace alinous */

#endif /* SQL_DML_PARTS_SQLLIMITOFFSET_H_ */
