/*
 * StringClassDeclare.cpp
 *
 *  Created on: 2020/03/16
 *      Author: iizuka
 */

#include "reserved_classes_string/StringClassDeclare.h"

namespace alinous {

StringClassDeclare::StringClassDeclare() {

}

StringClassDeclare::~StringClassDeclare() {
}

const UnicodeString* StringClassDeclare::getName() noexcept {
}

const UnicodeString* StringClassDeclare::getFullQualifiedName() noexcept {
}

int StringClassDeclare::binarySize() const {
}

void StringClassDeclare::toBinary(ByteBuffer* out) {
}

void StringClassDeclare::fromBinary(ByteBuffer* in) {
}

ClassDeclare* StringClassDeclare::getBaseClass() const noexcept {
}

} /* namespace alinous */
