/*
 * AbstractAlterCommandLog.h
 *
 *  Created on: 2020/09/16
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_ALTER_ABSTRACTALTERCOMMANDLOG_H_
#define TRANSACTION_LOG_ALTER_ABSTRACTALTERCOMMANDLOG_H_

#include "transaction_log/AbstractDdlLog.h"

namespace alinous {
class TableIdentifier;
class VirtualMachine;
class AnalyzeContext;
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

	virtual void initCommandParam(VirtualMachine* vm) = 0;

protected:
	TableIdentifier* tableId;
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_ALTER_ABSTRACTALTERCOMMANDLOG_H_ */
