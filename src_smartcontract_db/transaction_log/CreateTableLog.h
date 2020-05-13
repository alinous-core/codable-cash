/*
 * CreateTableLog.h
 *
 *  Created on: 2020/05/12
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_CREATETABLELOG_H_
#define TRANSACTION_LOG_CREATETABLELOG_H_

#include "transaction_log/AbstractDdlLog.h"

namespace codablecash {

class CdbTable;

class CreateTableLog : public AbstractDdlLog {
public:
	CreateTableLog();
	virtual ~CreateTableLog();

	virtual int binarySize() const noexcept;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	void setTable(CdbTable* table) noexcept;
private:
	CdbTable* table;
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_CREATETABLELOG_H_ */
