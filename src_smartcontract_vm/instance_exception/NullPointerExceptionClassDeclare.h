/*
 * NullPointerExceptionClassDeclare.h
 *
 *  Created on: 2020/04/17
 *      Author: iizuka
 */

#ifndef INSTANCE_EXCEPTION_NULLPOINTEREXCEPTIONCLASSDECLARE_H_
#define INSTANCE_EXCEPTION_NULLPOINTEREXCEPTIONCLASSDECLARE_H_

#include "reserved_classes/AbstractReservedClassDeclare.h"

namespace alinous {

class NullPointerExceptionClassDeclare : public AbstractReservedClassDeclare {
public:
	static UnicodeString NAME;

	NullPointerExceptionClassDeclare();
	virtual ~NullPointerExceptionClassDeclare();
};

} /* namespace alinous */

#endif /* INSTANCE_EXCEPTION_NULLPOINTEREXCEPTIONCLASSDECLARE_H_ */
