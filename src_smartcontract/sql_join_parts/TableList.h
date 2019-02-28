/*
 * TableList.h
 *
 *  Created on: 2019/02/27
 *      Author: iizuka
 */

#ifndef SQL_JOIN_PARTS_TABLELIST_H_
#define SQL_JOIN_PARTS_TABLELIST_H_

#include "base/ArrayList.h"
#include "sql/AbstractJoinPart.h"

namespace alinous {

class TableIdentifier;

class TableList : public AbstractJoinPart {
public:
	TableList();
	virtual ~TableList();

	void addTable(TableIdentifier* tableId) noexcept;
private:
	ArrayList<TableIdentifier> list;
};

} /* namespace alinous */

#endif /* SQL_JOIN_PARTS_TABLELIST_H_ */
