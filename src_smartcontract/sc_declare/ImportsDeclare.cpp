/*
 * ImportsDeclare.cpp
 *
 *  Created on: 2019/06/17
 *      Author: iizuka
 */

#include "sc_declare/ImportsDeclare.h"
#include "sc_declare/ImportDeclare.h"

namespace alinous {

ImportsDeclare::ImportsDeclare() : CodeElement(CodeElement::IMPORTS_DECLARE) {

}

ImportsDeclare::~ImportsDeclare() {

}

void ImportsDeclare::addImport(ImportDeclare* imp) noexcept {
	this->list.addElement(imp);
}

int ImportsDeclare::binarySize() const {
	int total = sizeof(uint16_t);

	total += sizeof(uint32_t);
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		ImportDeclare* imp = this->list.get(i);
		total += imp->binarySize();
	}

	return total;
}

void ImportsDeclare::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::IMPORTS_DECLARE);

	int maxLoop = this->list.size();
	out->putInt(maxLoop);
	for(int i = 0; i != maxLoop; ++i){
		ImportDeclare* imp = this->list.get(i);
		imp->toBinary(out);
	}
}

void ImportsDeclare::fromBinary(ByteBuffer* in) {
	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = CodeElement::createFromBinary(in);
		CodeElement::checkIsImport(element);

		this->list.addElement(dynamic_cast<ImportDeclare*>(element));
	}
}

} /* namespace alinous */
