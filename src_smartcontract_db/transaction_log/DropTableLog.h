/*
 * DropTableLog.h
 *
 *  Created on: 2020/10/09
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_DROPTABLELOG_H_
#define TRANSACTION_LOG_DROPTABLELOG_H_

#include "transaction_log/AbstractDdlLog.h"

namespace alinous {
class TableIdentifier;
}
using namespace alinous;

namespace codablecash {

class DropTableLog : public AbstractDdlLog {
public:
	DropTableLog();
	virtual ~DropTableLog();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	virtual void commit(CdbTransactionManager* trxManager);

	void setTableId(const TableIdentifier* tableId) noexcept;
	const TableIdentifier* getTableId() const noexcept {
		return tableId;
	}

private:
	TableIdentifier* tableId;
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_DROPTABLELOG_H_ */
