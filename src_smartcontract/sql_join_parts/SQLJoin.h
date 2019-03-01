/*
 * SQLJoin.h
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#ifndef SQL_DML_PARTS_SQLJOIN_H_
#define SQL_DML_PARTS_SQLJOIN_H_

#include "sql/AbstractJoinPart.h"
#include <cstdint>

#include "base/ArrayList.h"


namespace alinous {

class SQLJoinPart;

class SQLJoin : public AbstractJoinPart {
public:
	SQLJoin();
	virtual ~SQLJoin();

	void setFirst(AbstractJoinPart* first) noexcept;
	void addJoinPart(SQLJoinPart* part) noexcept;
private:
	AbstractJoinPart* first;
	ArrayList<SQLJoinPart> list;
};

} /* namespace alinous */

#endif /* SQL_DML_PARTS_SQLJOIN_H_ */
