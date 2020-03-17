/*
 * AbstractReservedClassDeclare.h
 *
 *  Created on: 2020/03/17
 *      Author: iizuka
 */

#ifndef RESERVED_CLASSES_ABSTRACTRESERVEDCLASSDECLARE_H_
#define RESERVED_CLASSES_ABSTRACTRESERVEDCLASSDECLARE_H_

#include "sc_declare/ClassDeclare.h"


namespace alinous {

class AbstractReservedClassDeclare : public ClassDeclare {
public:
	AbstractReservedClassDeclare();
	virtual ~AbstractReservedClassDeclare();


	virtual ArrayList<MethodDeclare>* getMethods() noexcept;
	virtual ArrayList<MemberVariableDeclare>* getMemberVariables() noexcept;

protected:
	ArrayList<MethodDeclare>* methods;
	ArrayList<MemberVariableDeclare>* members;
};

} /* namespace alinous */

#endif /* RESERVED_CLASSES_ABSTRACTRESERVEDCLASSDECLARE_H_ */
