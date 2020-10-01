/*
 * AlterModifyCommand.h
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_MODIFY_ALTERMODIFYCOMMAND_H_
#define SQL_DDL_ALTER_MODIFY_ALTERMODIFYCOMMAND_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

namespace codablecash {
class AlterModifyCommandLog;
}
using namespace codablecash;

namespace alinous {

class DdlColumnDescriptor;
class VirtualMachine;

class AlterModifyCommand : public AbstractAlterDdlCommand {
public:
	AlterModifyCommand(const AlterModifyCommand& inst);
	AlterModifyCommand();
	virtual ~AlterModifyCommand();

	void setColumnDescriptor(DdlColumnDescriptor* columnDescriptor) noexcept;
	const DdlColumnDescriptor* getColumnDescriptor() const noexcept {
		return columnDescriptor;
	}

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AbstractAlterCommandLog* getCommandLog();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual void interpret(VirtualMachine* vm, AbstractAlterCommandLog* log);

	int64_t getLengthValue() const noexcept {
		return this->longValue;
	}

private:
	void validate(VirtualMachine* vm, AlterModifyCommandLog* log);

private:
	DdlColumnDescriptor* columnDescriptor;
	int64_t longValue;
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_MODIFY_ALTERMODIFYCOMMAND_H_ */
