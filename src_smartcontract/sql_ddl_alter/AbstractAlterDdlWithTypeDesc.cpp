/*
 * AbstractAlterDdlWithTypeDesc.cpp
 *
 *  Created on: 2020/10/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AbstractAlterDdlWithTypeDesc.h"

#include "sql_ddl/DdlColumnDescriptor.h"

#include "sql/AbstractSQLExpression.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"

#include "base_io/ByteBuffer.h"

#include "instance_gc/StackFloatingVariableHandler.h"

#include "instance/IAbstractVmInstanceSubstance.h"
#include "instance/VmInstanceTypesConst.h"
#include "instance/AbstractVmInstance.h"

#include "instance_ref/PrimitiveReference.h"

#include "instance_string/VmStringInstance.h"


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

UnicodeString* AbstractAlterDdlWithTypeDesc::interpretDefaultString(VirtualMachine* vm) {
	UnicodeString* ret = nullptr;

	AbstractSQLExpression* defaultValue = this->columnDescriptor->getDefaultValue();
	if(defaultValue != nullptr){
		StackFloatingVariableHandler releaser(vm->getGc());

		AbstractVmInstance* inst = defaultValue->interpret(vm);
		releaser.registerInstance(inst);

		IAbstractVmInstanceSubstance* sub = inst != nullptr ? inst->getInstance() : nullptr;

		uint8_t instType = sub != nullptr ? sub->getInstType() : VmInstanceTypesConst::INST_NULL;

		if(instType == VmInstanceTypesConst::INST_NULL){
			ret = nullptr;
		}
		else if(sub->instIsPrimitive()){
			PrimitiveReference* pr = dynamic_cast<PrimitiveReference*>(sub);
			const UnicodeString* str = pr->toString();

			ret = new UnicodeString(str);
		}
		else if(VmInstanceTypesConst::INST_STRING == instType){
			VmStringInstance* strInst = dynamic_cast<VmStringInstance*>(sub);
			const UnicodeString* str = strInst->toString();

			ret = new UnicodeString(new UnicodeString(str));
		}
		//else{ Not necessary
		//	TypeCastExceptionClassDeclare::throwException(vm, this);
		//	ExceptionInterrupt::interruptPoint(vm);
		//}
	}

	return ret;
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
