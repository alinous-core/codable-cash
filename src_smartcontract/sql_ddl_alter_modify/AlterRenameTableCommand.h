/*
 * AlterRenameTableCommand.h
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_MODIFY_ALTERRENAMETABLECOMMAND_H_
#define SQL_DDL_ALTER_MODIFY_ALTERRENAMETABLECOMMAND_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

namespace alinous {

class UnicodeString;

class AlterRenameTableCommand : public AbstractAlterDdlCommand {
public:
	AlterRenameTableCommand();
	virtual ~AlterRenameTableCommand();

	void setNewName(UnicodeString* name) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

private:
	UnicodeString* newName;
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_MODIFY_ALTERRENAMETABLECOMMAND_H_ */
