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

AbstractCdbValue* VmInstanceValueConverter::toCdbValue(IAbstractVmInstanceSubstance* substance) {
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
		pref = dynamic_cast<PrimitiveReference*>(substance);
		value = new CdbByteValue(pref->getByteValue());
		break;
	case VmInstanceTypesConst::REF_CHAR:
	case VmInstanceTypesConst::REF_SHORT:
		pref = dynamic_cast<PrimitiveReference*>(substance);
		value = new CdbShortValue(pref->getShortValue());
		break;
	case VmInstanceTypesConst::REF_INT:
		pref = dynamic_cast<PrimitiveReference*>(substance);
		value = new CdbIntValue(pref->getIntValue());
		break;
	case VmInstanceTypesConst::REF_LONG:
		pref = dynamic_cast<PrimitiveReference*>(substance);
		value = new CdbLongValue(pref->getLongValue());
		break;
	default:
		// FIXME toCdbValue()
		break;
	}

	return value;
}

} /* namespace codablecash */
