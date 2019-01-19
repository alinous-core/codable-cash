/*
 * AbstractPrimitiveType.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "sc_declare_types/AbstractPrimitiveType.h"

namespace alinous {

AbstractPrimitiveType::AbstractPrimitiveType(short kind) : CodeElement(kind), ITypeDeclare() {
}

AbstractPrimitiveType::~AbstractPrimitiveType() {
}

} /* namespace alinous */
