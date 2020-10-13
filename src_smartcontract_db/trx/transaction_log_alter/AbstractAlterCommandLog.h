/*
 * AbstractAlterCommandLog.h
 *
 *  Created on: 2020/09/16
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_ALTER_ABSTRACTALTERCOMMANDLOG_H_
#define TRANSACTION_LOG_ALTER_ABSTRACTALTERCOMMANDLOG_H_

#include "trx/transaction_log/AbstractDdlLog.h"

namespace alinous {
class TableIdentifier;
class VirtualMachine;
class AnalyzeContext;
class CodeElement;
class TableIdentifier;
}
using namespace alinous;

namespace codablecash {

class AbstractAlterCommandLog : public AbstractDdlLog {
public:
	explicit AbstractAlterCommandLog(uint8_t type);
	virtual ~AbstractAlterCommandLog();

	void setTableIdentifier(const TableIdentifier* tableId) noexcept;
	const TableIdentifier* getTableId() const noexcept {
		return tableId;
	}

	virtual void reanalyze(AnalyzeContext* actx, CodeElement* parent);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	virtual void initCommandParam(VirtualMachine* vm, TableIdentifier* tableId) = 0;

protected:
	TableIdentifier* tableId;
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_ALTER_ABSTRACTALTERCOMMANDLOG_H_ */
