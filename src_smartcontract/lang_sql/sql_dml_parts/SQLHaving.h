/*
 * SQLHaving.h
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#ifndef SQL_DML_PARTS_SQLHAVING_H_
#define SQL_DML_PARTS_SQLHAVING_H_

#include "sql/AbstractSQLPart.h"

namespace alinous {
class AbstractSQLExpression;

class SQLHaving : public AbstractSQLPart {
public:
	SQLHaving();
	virtual ~SQLHaving();

	void setExpression(AbstractSQLExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	AbstractSQLExpression* exp;
};

} /* namespace alinous */

#endif /* SQL_DML_PARTS_SQLHAVING_H_ */
