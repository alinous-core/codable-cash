/*
 * AbstractAlterDdlWithTypeDesc.h
 *
 *  Created on: 2020/10/08
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_ABSTRACTALTERDDLWITHTYPEDESC_H_
#define SQL_DDL_ALTER_ABSTRACTALTERDDLWITHTYPEDESC_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

namespace alinous {

class DdlColumnDescriptor;

class AbstractAlterDdlWithTypeDesc : public AbstractAlterDdlCommand {
public:
	explicit AbstractAlterDdlWithTypeDesc(short kind);
	virtual ~AbstractAlterDdlWithTypeDesc();

	void setColumnDescriptor(DdlColumnDescriptor* columnDescriptor) noexcept;
	const DdlColumnDescriptor* getColumnDescriptor() const noexcept {
		return columnDescriptor;
	}
	int64_t getLengthValue() const noexcept {
		return this->longValue;
	}

protected:
	DdlColumnDescriptor* copyColumnDescriptor(DdlColumnDescriptor* columnDescriptor) const;

protected:
	DdlColumnDescriptor* columnDescriptor;
	int64_t longValue;
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_ABSTRACTALTERDDLWITHTYPEDESC_H_ */
