/*
 * SQLSelectTargetList.h
 *
 *  Created on: 2019/02/23
 *      Author: iizuka
 */

#ifndef SQL_DML_PARTS_SQLSELECTTARGETLIST_H_
#define SQL_DML_PARTS_SQLSELECTTARGETLIST_H_

#include "sql/AbstractSQLPart.h"
#include "base/ArrayList.h"

namespace alinous {
class SQLSelectTarget;

class SQLSelectTargetList : public AbstractSQLPart {
public:
	SQLSelectTargetList();
	virtual ~SQLSelectTargetList();

	void addTarget(SQLSelectTarget* target) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	ArrayList<SQLSelectTarget> list;
};

} /* namespace alinous */

#endif /* SQL_DML_PARTS_SQLSELECTTARGETLIST_H_ */
