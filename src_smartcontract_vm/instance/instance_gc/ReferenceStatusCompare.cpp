/*
 * ReferenceStatusCompare.cpp
 *
 *  Created on: 2020/01/12
 *      Author: iizuka
 */

#include "instance/instance_gc/ReferenceStatusCompare.h"
#include "instance/instance_gc/ReferenceStatus.h"

namespace alinous {

int ReferenceStatusCompare::operator ()(const ReferenceStatus* const a, const ReferenceStatus* const b) const noexcept {
	long long diff = (long long)a->instance - (long long)b->instance;
	if(diff == 0){
		return 0;
	}
	return diff > 0 ? 1 : -1;
}

} /* namespace alinous */
