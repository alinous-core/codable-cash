/*
 * StaticClassMetadata.cpp
 *
 *  Created on: 2020/04/30
 *      Author: iizuka
 */

#include "instance_ref_class_static_meta/StaticClassMetadata.h"

namespace alinous {

StaticClassMetadata::StaticClassMetadata(AnalyzedClass* clazz) {
	this->clazz = clazz;
}

StaticClassMetadata::~StaticClassMetadata() {
	this->clazz = nullptr;
}

void StaticClassMetadata::init() noexcept {

}

} /* namespace alinous */
