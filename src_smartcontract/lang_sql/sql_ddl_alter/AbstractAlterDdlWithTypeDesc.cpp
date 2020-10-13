/*
 * AbstractAlterDdlWithTypeDesc.cpp
 *
 *  Created on: 2020/10/08
 *      Author: iizuka
 */

#include "lang_sql/sql_ddl_alter/AbstractAlterDdlWithTypeDesc.h"

#include "lang_sql/sql_ddl/DdlColumnDescriptor.h"
#include "lang_sql/sql_ddl/ColumnTypeDescriptor.h"

#include "lang_sql/sql/AbstractSQLExpression.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"

#include "base_io/ByteBuffer.h"

#include "instance/instance_gc/StackFloatingVariableHandler.h"

#include "instance/IAbstractVmInstanceSubstance.h"
#include "instance/VmInstanceTypesConst.h"
#include "instance/AbstractVmInstance.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "instance/instance_string/VmStringInstance.h"

#include "lang_sql/sql_expression/SQLLiteral.h"

#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/ValidationError.h"

namespace alinous {

AbstractAlterDdlWithTypeDesc::AbstractAlterDdlWithTypeDesc(short kind) : AbstractAlterDdlCommand(kind) {
	this->columnDescriptor = nullptr;
	this->longValue = 0;
	this->defaultValueStr = nullptr;
}

AbstractAlterDdlWithTypeDesc::~AbstractAlterDdlWithTypeDesc() {
	delete columnDescriptor;
	delete this->defaultValueStr;
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

			ret = new UnicodeString(str);
		}
		//else{ Not necessary
		//	TypeCastExceptionClassDeclare::throwException(vm, this);
		//	ExceptionInterrupt::interruptPoint(vm);
		//}
	}

	return ret;
}

void AbstractAlterDdlWithTypeDesc::analyzeLengthOfValiable(AnalyzeContext* actx) {
	ColumnTypeDescriptor* typeDesc = this->columnDescriptor->getTypeDesc();

	AbstractSQLExpression* length = typeDesc->getLengthExp();

	if(length != nullptr){
		bool error = false;
		short kind = length->getKind();
		if(kind != CodeElement::SQL_EXP_LITERAL){
			const UnicodeString* tname = typeDesc->getTypeName();
			actx->addValidationError(ValidationError::DB_LENGTH_IS_NOT_INTEGER, this, L"The type {0}'s length must be integer value.", {tname});

			error = true;
		}

		if(!error){
			SQLLiteral* lit = dynamic_cast<SQLLiteral*>(length);
			uint8_t litType = lit->getLiteralType();
			if(litType != SQLLiteral::TYPE_NUMBER){
				const UnicodeString* tname = typeDesc->getTypeName();
				actx->addValidationError(ValidationError::DB_LENGTH_IS_NOT_INTEGER, this, L"The type {0}'s length must be integer value.", {tname});
			}

			lit->analyze(actx);

			this->longValue = lit->getLongv();
			if(this->longValue < 1){
				const UnicodeString* tname = typeDesc->getTypeName();
				actx->addValidationError(ValidationError::DB_LENGTH_IS_NOT_CORRECT_INTEGER, this, L"The type {0}'s length must be greater than 0.", {tname});
			}
		}
	}
}

void AbstractAlterDdlWithTypeDesc::setDefaultValueStr(UnicodeString* str) noexcept {
	delete this->defaultValueStr;
	this->defaultValueStr = str;
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
