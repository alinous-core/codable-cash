/*
 * ConstStaticPrimitive.cpp
 *
 *  Created on: 2020/03/24
 *      Author: iizuka
 */

#include "instance_ref/ConstStaticPrimitive.h"

namespace alinous {

ConstStaticPrimitive::ConstStaticPrimitive(PrimitiveReference* primitiveObj) : PrimitiveReference(primitiveObj->getType()) {

}

ConstStaticPrimitive::~ConstStaticPrimitive() {

}

bool ConstStaticPrimitive::isStaticConst() const noexcept {
	return true;
}

} /* namespace alinous */
