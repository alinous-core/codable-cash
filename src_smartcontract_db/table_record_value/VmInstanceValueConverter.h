/*
 * VmInstanceValueConverter.h
 *
 *  Created on: 2020/06/17
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_VALUE_VMINSTANCEVALUECONVERTER_H_
#define TABLE_RECORD_VALUE_VMINSTANCEVALUECONVERTER_H_

namespace alinous {
class IAbstractVmInstanceSubstance;
}
using namespace alinous;

namespace codablecash {

class AbstractCdbValue;

class VmInstanceValueConverter {
public:
	static AbstractCdbValue* toCdbValue(IAbstractVmInstanceSubstance* substance);
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_VALUE_VMINSTANCEVALUECONVERTER_H_ */
