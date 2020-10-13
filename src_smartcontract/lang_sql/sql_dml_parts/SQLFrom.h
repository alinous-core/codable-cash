/*
 * SQLFrom.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_PARTS_SQLFROM_H_
#define SQL_DML_PARTS_SQLFROM_H_

#include "lang_sql/sql/AbstractSQLPart.h"

namespace alinous {
class TableIdentifier;
class AbstractJoinPart;

class SQLFrom : public AbstractSQLPart {
public:
	SQLFrom();
	virtual ~SQLFrom();

	void setTable(AbstractJoinPart* tableId) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	AbstractJoinPart* getTablePart() const noexcept;
private:
	AbstractJoinPart* tableId;
};

} /* namespace alinous */

#endif /* SQL_DML_PARTS_SQLFROM_H_ */
