/*
 * AbstractExceptionClassDeclare.h
 *
 *  Created on: 2020/04/18
 *      Author: iizuka
 */

#ifndef INSTANCE_EXCEPTION_CLASS_ABSTRACTEXCEPTIONCLASSDECLARE_H_
#define INSTANCE_EXCEPTION_CLASS_ABSTRACTEXCEPTIONCLASSDECLARE_H_

#include "instance/reserved_classes/AbstractReservedClassDeclare.h"

namespace alinous {

class AnalyzedClass;

class AbstractExceptionClassDeclare : public AbstractReservedClassDeclare {
public:
	AbstractExceptionClassDeclare();
	virtual ~AbstractExceptionClassDeclare();
};

} /* namespace alinous */

#endif /* INSTANCE_EXCEPTION_CLASS_ABSTRACTEXCEPTIONCLASSDECLARE_H_ */
