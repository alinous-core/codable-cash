/*
 * ImportDeclare.cpp
 *
 *  Created on: 2019/06/17
 *      Author: iizuka
 */

#include "sc_declare/ImportDeclare.h"

namespace alinous {

ImportDeclare::ImportDeclare() : CodeElement(CodeElement::IMPORT_DECLARE) {

}

ImportDeclare::~ImportDeclare() {

}

int ImportDeclare::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void ImportDeclare::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::IMPORTS_DECLARE);
}

void ImportDeclare::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
