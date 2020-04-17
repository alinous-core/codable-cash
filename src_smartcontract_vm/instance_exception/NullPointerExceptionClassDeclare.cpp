/*
 * NullPointerExceptionClassDeclare.cpp
 *
 *  Created on: 2020/04/17
 *      Author: iizuka
 */

#include "instance_exception/NullPointerExceptionClassDeclare.h"

#include "base/UnicodeString.h"


namespace alinous {

UnicodeString NullPointerExceptionClassDeclare::NAME{L"NullPointerException"};

NullPointerExceptionClassDeclare::NullPointerExceptionClassDeclare() : AbstractReservedClassDeclare() {
	addDefaultConstructor(&NAME);
}

NullPointerExceptionClassDeclare::~NullPointerExceptionClassDeclare() {

}

} /* namespace alinous */
