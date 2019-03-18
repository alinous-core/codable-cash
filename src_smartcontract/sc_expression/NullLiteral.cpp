/*
 * NullLiteral.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/NullLiteral.h"

namespace alinous {

NullLiteral::NullLiteral() : AbstractExpression(CodeElement::EXP_NULL_LITERAL) {
}

NullLiteral::~NullLiteral() {

}

} /* namespace alinous */

int alinous::NullLiteral::binarySize() const {
}

void alinous::NullLiteral::toBinary(ByteBuffer* out) {
}

void alinous::NullLiteral::fromBinary(ByteBuffer* in) {
}
