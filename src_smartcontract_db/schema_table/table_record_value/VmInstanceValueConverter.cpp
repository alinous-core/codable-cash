/*
 * VmInstanceValueConverter.cpp
 *
 *  Created on: 2020/06/17
 *      Author: iizuka
 */

#include "schema_table/table_record_value/VmInstanceValueConverter.h"

#include "instance/IAbstractVmInstanceSubstance.h"
#include "instance/VmInstanceTypesConst.h"

#include "instance_ref/PrimitiveReference.h"

#include "schema_table/table_record_value/AbstractCdbValue.h"
#include "schema_table/table_record_value/CdbByteValue.h"
#include "schema_table/table_record_value/CdbShortValue.h"
#include "schema_table/table_record_value/CdbIntValue.h"
#include "schema_table/table_record_value/CdbLongValue.h"
#include "schema_table/table_record_value/CdbStringValue.h"

#include "instance_string/VmStringInstance.h"

#include "engine/CdbException.h"


namespace codablecash {

AbstractCdbValue* VmInstanceValueConverter::toCdbValue(IAbstractVmInstanceSubstance* substance, uint8_t targetCdbColumnType) {
	if(substance == nullptr){
		return nullptr;
	}

	uint8_t type = substance->getInstType();
	AbstractCdbValue* value = nullptr;

	PrimitiveReference* pref = nullptr;
	VmStringInstance* strInst = nullptr;

	switch(type){
	case VmInstanceTypesConst::INST_STRING:
		strInst = dynamic_cast<VmStringInstance*>(substance);
		value = new CdbStringValue(strInst->toString());
		break;
	case VmInstanceTypesConst::REF_BOOL:
	case VmInstanceTypesConst::REF_BYTE:
	case VmInstanceTypesConst::REF_CHAR:
	case VmInstanceTypesConst::REF_SHORT:
	case VmInstanceTypesConst::REF_INT:
	case VmInstanceTypesConst::REF_LONG:
		pref = dynamic_cast<PrimitiveReference*>(substance);
		value = fromPrimitiveToCdbValue(pref, targetCdbColumnType);
		break;
	default:
		throw new CdbException(L"Column type and value don't have compatibility.", __FILE__, __LINE__);
		break;
	}

	return value;
}

AbstractCdbValue* VmInstanceValueConverter::fromPrimitiveToCdbValue(PrimitiveReference* pref, uint8_t targetCdbColumnType) {
	AbstractCdbValue* value = nullptr;

	switch(targetCdbColumnType){
	case AbstractCdbValue::TYPE_BYTE:
		value = new CdbByteValue(pref->getByteValue());
		break;
	case AbstractCdbValue::TYPE_SHORT:
		value = new CdbShortValue(pref->getShortValue());
		break;
	case AbstractCdbValue::TYPE_INT:
		value = new CdbIntValue(pref->getIntValue());
		break;
	case AbstractCdbValue::TYPE_LONG:
		value = new CdbLongValue(pref->getLongValue());
		break;
	default:
		throw new CdbException(L"Column type and value don't have compatibility.", __FILE__, __LINE__);
		break;
	}

	return value;
}

} /* namespace codablecash */
