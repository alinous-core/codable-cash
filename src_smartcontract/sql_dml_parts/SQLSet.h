/*
 * SQLSet.h
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#ifndef SQL_DML_PARTS_SQLSET_H_
#define SQL_DML_PARTS_SQLSET_H_

#include "sql/AbstractSQLPart.h"
#include "base/ArrayList.h"

namespace alinous {

class SQLSetPair;

class SQLSet : public AbstractSQLPart {
public:
	SQLSet();
	virtual ~SQLSet();

	void addPair(SQLSetPair* pair) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	ArrayList<SQLSetPair> list;
};

} /* namespace alinous */

#endif /* SQL_DML_PARTS_SQLSET_H_ */
