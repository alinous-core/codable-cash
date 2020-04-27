/*
 * StaticClassEntry.cpp
 *
 *  Created on: 2020/04/25
 *      Author: iizuka
 */

#include "instance_ref_class_static/StaticClassEntry.h"

#include "sc_analyze/AnalyzedClass.h"


namespace alinous {

StaticClassEntry::StaticClassEntry(AnalyzedClass* aclazz) {
	this->aclazz = aclazz;
}

StaticClassEntry::~StaticClassEntry() {
	this->aclazz = nullptr;
}

} /* namespace alinous */
