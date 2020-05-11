/*
 * SchemaBinary.cpp
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#include "schema/SchemaBinary.h"

#include "base/UnicodeString.h"

namespace codablecash {

SchemaBinary::SchemaBinary() {

}

SchemaBinary::~SchemaBinary() {
	this->list.deleteElements();
}

void SchemaBinary::addSchemaName(const UnicodeString* name) noexcept {
	this->list.addElement(new UnicodeString(name));
}


} /* namespace codablecash */
