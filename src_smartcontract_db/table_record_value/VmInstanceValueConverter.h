/*
 * VmInstanceValueConverter.h
 *
 *  Created on: 2020/06/17
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_VALUE_VMINSTANCEVALUECONVERTER_H_
#define TABLE_RECORD_VALUE_VMINSTANCEVALUECONVERTER_H_
#include <cstdint>

namespace alinous {
class IAbstractVmInstanceSubstance;
class PrimitiveReference;
class VmStringInstance;
}
using namespace alinous;

namespace codablecash {

class AbstractCdbValue;

class VmInstanceValueConverter {
public:
	static AbstractCdbValue* toCdbValue(IAbstractVmInstanceSubstance* substance, uint8_t targetCdbColumnType);

private:
	static AbstractCdbValue* fromStringToCdbValue(VmStringInstance* strInst, uint8_t targetCdbColumnType);
	static AbstractCdbValue* fromPrimitiveToCdbValue(PrimitiveReference* pref, uint8_t targetCdbColumnType);
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_VALUE_VMINSTANCEVALUECONVERTER_H_ */
