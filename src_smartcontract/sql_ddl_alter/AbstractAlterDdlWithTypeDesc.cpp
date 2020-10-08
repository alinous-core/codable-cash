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
	this->columnDescriptor = nullptr;
	this->longValue = 0;
}

AbstractAlterDdlWithTypeDesc::~AbstractAlterDdlWithTypeDesc() {

}

void AbstractAlterDdlWithTypeDesc::setColumnDescriptor(DdlColumnDescriptor* columnDescriptor) noexcept {
	delete this->columnDescriptor;
	this->columnDescriptor = columnDescriptor;
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
