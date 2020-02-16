/*
 * VmArrayInstanceUtils.h
 *
 *  Created on: 2020/02/16
 *      Author: iizuka
 */

#ifndef INSTANCE_ARRAY_VMARRAYINSTANCEUTILS_H_
#define INSTANCE_ARRAY_VMARRAYINSTANCEUTILS_H_

namespace alinous {

class AnalyzedType;

class VmArrayInstanceUtils {
public:
	static bool isArrayIndex(AnalyzedType& type) noexcept;
};

} /* namespace alinous */

#endif /* INSTANCE_ARRAY_VMARRAYINSTANCEUTILS_H_ */
