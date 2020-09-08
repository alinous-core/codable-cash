/*
 * AlterAddColumnCommand.h
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_ALTERADDCOLUMNCOMMAND_H_
#define SQL_DDL_ALTER_ALTERADDCOLUMNCOMMAND_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

namespace alinous {

class AlterAddColumnCommand : public AbstractAlterDdlCommand {
public:
	explicit AlterAddColumnCommand(short kind);
	virtual ~AlterAddColumnCommand();
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_ALTERADDCOLUMNCOMMAND_H_ */
