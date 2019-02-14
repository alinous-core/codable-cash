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
