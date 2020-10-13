/*
 * ConstStaticPrimitive.cpp
 *
 *  Created on: 2020/03/24
 *      Author: iizuka
 */

#include "instance/instance_ref/ConstStaticPrimitive.h"

#include "osenv/memory.h"

namespace alinous {

ConstStaticPrimitive::ConstStaticPrimitive(PrimitiveReference* primitiveObj) : PrimitiveReference(primitiveObj->getType()) {
	size_t size = primitiveObj->getDataSize(primitiveObj->getType());

	this->type = primitiveObj->getType();
	this->malloc = primitiveObj->getMalloc();
	this->data = this->malloc->mallocPtrArray(size);

	void* pdata = primitiveObj->getData();

	Mem::memcpy(this->data, pdata, size);
}

ConstStaticPrimitive::~ConstStaticPrimitive() {

}

bool ConstStaticPrimitive::isStaticConst() const noexcept {
	return true;
}

} /* namespace alinous */
