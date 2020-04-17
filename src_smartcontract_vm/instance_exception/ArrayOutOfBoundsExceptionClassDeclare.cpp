/*
 * ArrayOutOfBoundsExceptionClassDeclare.cpp
 *
 *  Created on: 2020/04/17
 *      Author: iizuka
 */

#include "instance_exception/ArrayOutOfBoundsExceptionClassDeclare.h"

#include "base/UnicodeString.h"


namespace alinous {

UnicodeString ArrayOutOfBoundsExceptionClassDeclare::NAME{L"ArrayOutOfBoundsException"};

ArrayOutOfBoundsExceptionClassDeclare::ArrayOutOfBoundsExceptionClassDeclare() : AbstractReservedClassDeclare() {
	addDefaultConstructor(&NAME);
}

ArrayOutOfBoundsExceptionClassDeclare::~ArrayOutOfBoundsExceptionClassDeclare() {

}

} /* namespace alinous */
