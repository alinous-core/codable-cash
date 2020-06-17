/*
 * VmInstanceValueConverter.cpp
 *
 *  Created on: 2020/06/17
 *      Author: iizuka
 */

#include "table_record_value/VmInstanceValueConverter.h"

#include "instance/IAbstractVmInstanceSubstance.h"
#include "instance/VmInstanceTypesConst.h"

#include "instance_ref/PrimitiveReference.h"

#include "table_record_value/CdbByteValue.h"
#include "table_record_value/CdbShortValue.h"
#include "table_record_value/CdbIntValue.h"
#include "table_record_value/CdbLongValue.h"
#include "table_record_value/CdbStringValue.h"

#include "instance_string/VmStringInstance.h"


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
		// FIXME toCdbValue()
		break;
	}

	return value;
}

AbstractCdbValue* VmInstanceValueConverter::fromPrimitiveToCdbValue(PrimitiveReference* pref, uint8_t targetCdbColumnType) {
	AbstractCdbValue* value = nullptr;

	switch(targetCdbColumnType){
	default:
		break;
	}

	return value;
}

} /* namespace codablecash */
