/*
 * AlterRecordValueExecutor.h
 *
 *  Created on: 2020/10/09
 *      Author: iizuka
 */

#ifndef TABLE_STORE_ALTERRECORDVALUEEXECUTOR_H_
#define TABLE_STORE_ALTERRECORDVALUEEXECUTOR_H_

namespace codablecash {

class CdbTableColumn;
class TableStore;

class AlterRecordValueExecutor {
public:
	explicit AlterRecordValueExecutor(const CdbTableColumn* column);
	virtual ~AlterRecordValueExecutor();

	void addColumn(TableStore* store);
	void removeColumn(TableStore* store);

private:
	const CdbTableColumn* column;
};

} /* namespace codablecash */

#endif /* TABLE_STORE_ALTERRECORDVALUEEXECUTOR_H_ */
