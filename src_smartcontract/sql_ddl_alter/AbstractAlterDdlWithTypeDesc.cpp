/*
 * AbstractAlterDdlWithTypeDesc.cpp
 *
 *  Created on: 2020/10/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AbstractAlterDdlWithTypeDesc.h"

#include "sql_ddl/DdlColumnDescriptor.h"

#include "base/StackRelease.h"

#include "base_io/ByteBuffer.h"

namespace alinous {

AbstractAlterDdlWithTypeDesc::AbstractAlterDdlWithTypeDesc(short kind) : AbstractAlterDdlCommand(kind) {

}

AbstractAlterDdlWithTypeDesc::~AbstractAlterDdlWithTypeDesc() {

}

DdlColumnDescriptor* AbstractAlterDdlWithTypeDesc::copyColumnDescriptor(
		DdlColumnDescriptor* columnDescriptor) const {
	int size = columnDescriptor->binarySize();

	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	columnDescriptor->toBinary(buff);

	buff->position(0);

	CodeElement* element = CodeElement::createFromBinary(buff);

	return dynamic_cast<DdlColumnDescriptor*>(element);
}

} /* namespace alinous */
