/*
 * AlterDropPrimaryKeyCommand.h
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_MODIFY_ALTERDROPPRIMARYKEYCOMMAND_H_
#define SQL_DDL_ALTER_MODIFY_ALTERDROPPRIMARYKEYCOMMAND_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

namespace alinous {

class AlterDropPrimaryKeyCommand : public AbstractAlterDdlCommand {
public:
	AlterDropPrimaryKeyCommand(const AlterDropPrimaryKeyCommand& inst);
	AlterDropPrimaryKeyCommand();
	virtual ~AlterDropPrimaryKeyCommand();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AbstractDdlLog* getCommandLog();
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_MODIFY_ALTERDROPPRIMARYKEYCOMMAND_H_ */
